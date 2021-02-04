(function ($) {

  /**
   * Enables the autocomplete feature for corresponding fields.
   */
  Drupal.behaviors.reiscout_addressfield_autocomplete = {
    attach: function (context, settings) {
      $('#content', context).once('reiscout_addressfield_autocomplete', function () {
        $(Drupal.settings.reiscout_addressfield_autocomplete.fields).each(function(index, field_name) {
          var field_class = field_name.replace(/_/g, '-');

          // Show suggestions for US addresses only.
          var options = {
            country: 'us'
          };

          // IDs of fields result address will be put in.
          var fields_mapping = {
            locality: 'edit-' + field_class + '-und-0-locality',
            administrative_area_level_1: 'edit-' + field_class + '-und-0-administrative-area',
            postal_code: 'edit-' + field_class + '-und-0-postal-code'
          };

          var autocomplete_field_id = field_class + '-autocomplete';
          var autocomplete_field = '<input id="' + autocomplete_field_id + '" type="text" size="50" placeholder="e.g. 123 Some Street, Some City, GA" class="form-text required" />';

          var enter_address_manually_link_id = field_class + '-enter-address-manually';
          var enter_address_manually_link = '<a id="' + enter_address_manually_link_id + '">' + Drupal.t('Enter address manually »') + '</a>';

          var reset_address_link_id = field_class + '-reset-address';
          var reset_address_link = '<a id="' + reset_address_link_id + '">' + Drupal.t('Reset address »') + '</a>';

          function show_addressfield_widget() {
            $('#' + autocomplete_field_id).hide();
            $('#' + enter_address_manually_link_id).hide();
            $('#edit-' + field_class + '-und-0 .street-block').show('fade');
            $('#edit-' + field_class + '-und-0 .locality-block').show('fade');
            $('#' + reset_address_link_id).show('fade');
          }

          $('#edit-' + field_class + '-und-0 .street-block').before(autocomplete_field + enter_address_manually_link);
          $('#edit-' + field_class + '-und-0 .locality-block').after(reset_address_link);

          if ($('#edit-' + field_class + '-und-0-thoroughfare').val()) {
            $('#' + autocomplete_field_id).hide();
            $('#' + enter_address_manually_link_id).hide();
          }
          else {
            $('#edit-' + field_class + '-und-0 .street-block').hide();
            $('#edit-' + field_class + '-und-0 .locality-block').hide();
            $('#' + reset_address_link_id).hide();
          }

          $('#' + autocomplete_field_id)
            .geocomplete(options)
            .bind("geocode:result", function(event, result) {
              // Fill 'Address 1' field.
              $('#edit-' + field_class + '-und-0-thoroughfare').val(result.formatted_address.split(',')[0]);

              // Iterate over all components of result address and
              // fill the corresponding fields of the address widget.
              for (var i = 0; i < result.address_components.length; ++i) {
                var component_type = result.address_components[i].types[0];
                var field_id = fields_mapping[component_type];
                if ('undefined' !== typeof field_id) {
                  $('#' + field_id).val(result.address_components[i].short_name);
                }
              }

              show_addressfield_widget();
            });

          $('#' + enter_address_manually_link_id).click(function() {
            show_addressfield_widget();
            $('#edit-' + field_class + '-und-0-thoroughfare').focus();
          });

          $('#' + reset_address_link_id).click(function() {
            $('#edit-' + field_class + '-und-0-thoroughfare').val('');
            $('#edit-' + field_class + '-und-0-premise').val('');
            $('#edit-' + field_class + '-und-0-locality').val('');
            $('#edit-' + field_class + '-und-0-administrative-area').val('');
            $('#edit-' + field_class + '-und-0-postal-code').val('');
            $('#edit-' + field_class + '-und-0 .street-block').hide();
            $('#edit-' + field_class + '-und-0 .locality-block').hide();
            $('#' + reset_address_link_id).hide();
            $('#' + autocomplete_field_id).val('').show().focus();
            $('#' + enter_address_manually_link_id).show();
          });
        });
      });
    }
  };

})(jQuery);
