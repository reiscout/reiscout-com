(function ($) {
  Drupal.behaviors.reiscoutTextfieldClearButton = {
    attach: function (context, settings) {
      $('.clear-address-button[data-input-id]', context).once('clear-button', function (e) {
        $(this).bind('click', function (e) {
          e.preventDefault();

          $('#' + $(this).data('input-id')).val('');
        });
      });
    }
  };
})(jQuery);