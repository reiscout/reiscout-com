/**
 * Implements hook_form_alter().
 */
function reiscout_geocoder_form_alter(form, form_state, form_id) {
  try {
    if (
        form_id === 'node_edit'
        && form.bundle === 'property'
        && module_exists('geofield')
        && typeof form.elements.field_geo_position !== 'undefined'
        && form.elements.field_geo_position.type === 'geofield'
        && form.elements.field_geo_position.field_info_instance.widget.type === 'geofield_latlon'
        && typeof form.elements.field_address_text !== 'undefined'
        && form.elements.field_address_text.type === 'text'
    ) {
        var lang = language_default();
        if (typeof form.elements.field_address_text[lang] !== 'undefined') {
          for (var delta in form.elements.field_address_text[lang]) {
            form.elements.field_geo_position.reiscout_address_id = form.elements.field_address_text[lang][delta].id;
            form.elements.field_geo_position.field_info_instance.widget.module = 'reiscout_geocoder';
            break;
          }
        }
    }
  }
  catch (error) {
    console.log('reiscout_geocoder_form_alter - ' + error);
  }
}

/**
 * Implements hook_field_widget_form().
 */
function reiscout_geocoder_field_widget_form(form, form_state, field, instance, langcode, items, delta, element) {
  try {
    items[delta].type = 'hidden';

    if (items[delta].item) {
      items[delta].value = items[delta].item.lat + ',' + items[delta].item.lon;
    }

    items[delta].children.push({
      id: items[delta].id + '-btn',
      text: t('Get GPS Address'),
      type: 'button',
      options: {
        attributes: {
          onclick: "_reiscout_geocoder_field_widget_form_click('" + items[delta].id + "', '" + element.reiscout_address_id + "')"
        }
      }
    });
  }
  catch (error) { console.log('reiscout_geocoder_field_widget_form - ' + error); }
}

function _reiscout_geocoder_field_widget_form_click(id, address_id) {
  try {
    drupalgap_loading_message_show({
      text: t('Getting position and address') + '...',
      textVisible: true,
      theme: 'b'
    });

    navigator.geolocation.getCurrentPosition(
      function (position) {
        if (Drupal.settings.debug) {
          console.log(['_reiscout_geocoder_field_widget_form_click.getCurrentPosition.position', position]);
        }

        if (typeof position.coords.latitude !== 'undefined' && typeof position.coords.longitude !== 'undefined') {
          $('#' + id).val([position.coords.latitude, position.coords.longitude].join(','));

          Drupal.services.call({
            method: 'POST',
            path: 'geocoderapi/geocode_reverse.json',
            service: 'geocoderapi',
            resource: 'geocode_reverse',
            data: JSON.stringify({
              latitude: position.coords.latitude,
              longitude: position.coords.longitude
            }),
            success: function(result) {
              if (Drupal.settings.debug) {
                console.log(['_reiscout_geocoder_field_widget_form_click.geocode_reverse.success', result]);
              }

              $('#' + address_id).val(result.address);
            },
            error: function(xhr, status, message) {
              if (Drupal.settings.debug) {
                console.log(['_reiscout_geocoder_field_widget_form_click.geocode_reverse.error', xhr, status, message]);
              }

              drupalgap_alert(t('Could not detect your address. Please, enter address manually'));
            }
          });
        }
        else {
          drupalgap_alert(t('Could not detect your position. Please, enter address manually'));
        }
      },
      function (error) {
        drupalgap_loading_message_hide();

        if (Drupal.settings.debug) {
          console.log(['_reiscout_geocoder_field_widget_form_click.getCurrentPosition', error]);
        }

        drupalgap_alert(t('Could not detect your position. Please, enter address manually'));
      },
      {enableHighAccuracy: true}
    );
  }
  catch (error) {
    console.log('_reiscout_geocoder_field_widget_form_click - ' + error);

    drupalgap_loading_message_hide();
  }
}