/**
 * Implements hook_install().
 */
function reiscout_addressautocomplete_install() {
  try {
    var modulePath = drupalgap_get_path('module', 'reiscout_addressautocomplete');
    drupalgap_add_js('http://maps.googleapis.com/maps/api/js?libraries=places');
    drupalgap_add_js(modulePath + '/geocomplete/jquery.geocomplete' + (Drupal.settings.debug ? '' : '.min') + '.js');
    drupalgap_add_css(modulePath + '/reiscout_addressautocomplete.css');
  }
  catch (error) {
    console.log('reiscout_addressautocomplete_install - ' + error);
  }
}

/**
 * Implements hook_form_alter().
 */
function reiscout_addressautocomplete_form_alter(form, form_state, form_id) {
  try {
    if (
        form_id === 'node_edit'
        && form.bundle === 'property'
        && typeof form.elements.field_address_text !== 'undefined'
        && form.elements.field_address_text.type === 'text'
        && form.elements.field_address_text.field_info_instance.widget.module === 'text'
    ) {
        form.elements.field_address_text.field_info_instance.widget.module = 'reiscout_addressautocomplete';
    }
  }
  catch (error) {
    console.log('reiscout_addressautocomplete_form_alter - ' + error);
  }
}

/**
 * Implements hook_field_widget_form().
 */
function reiscout_addressautocomplete_field_widget_form(form, form_state, field, instance, langcode, items, delta, element) {
  try {
      if (function_exists('text_field_widget_form')) {
        text_field_widget_form(form, form_state, field, instance, langcode, items, delta, element);
      }
      
      items[delta].children.push({
        type: 'markup',
        markup: "<script type=\"text/javascript\">$('#" + items[delta].id + "').geocomplete();</script>"
      });
  }
  catch (error) {
    console.log('reiscout_addressautocomplete_field_widget_form - ' + error);
  }
}
