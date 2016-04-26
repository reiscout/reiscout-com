(function ($) {
  Drupal.behaviors.reiscoutTextfieldClearButton = {
    attach: function (context, settings) {
      $('.address-clear-button[data-input-id]', context).once('address-clear-button', function () {
        $(this).bind('click', function (e) {
          e.preventDefault();
          
          $('#' + $(this).data('input-id')).val('');
        });
      });

      $('.address-autocomplete[id]', context).once('address-autocomplete', function () {
        var $address = $(this);
        var placeholder = $address.prop('placeholder');

        $address.geocomplete();
        $address.prop('placeholder', placeholder);
      });
    }
  };
})(jQuery);