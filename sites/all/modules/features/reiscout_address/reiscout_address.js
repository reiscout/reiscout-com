(function ($) {
  Drupal.behaviors.reiscoutTextfieldClearButton = {
    attach: function (context, settings) {
      $('.clear-address-button[data-input-id]', context).once('clear-address-button', function () {
        $(this).bind('click', function (e) {
          e.preventDefault();

          $('#' + $(this).data('input-id')).val('');
        });
      });

      if (settings.reiscout_address_autocomplete instanceof Array) {
        for (var i = 0, j = settings.reiscout_address_autocomplete.length; i < j; i++) {
          $('#' + settings.reiscout_address_autocomplete[i], context).once('address-autocomplete-' + i, function () {
            var $address = $(this);
            var placeholder = $address.prop('placeholder');
            
            $address.geocomplete();
            $address.prop('placeholder', placeholder);
          })
        }
      }
    }
  };
})(jQuery);