(function ($) {

  /**
   * Attaches behaviors to Property Table Form.
   */
  Drupal.behaviors.propertyTableForm = {
    attach: function (context, settings) {
      $('#property-table-form', context).once('property-table-form', function () {
        function defineFilterVariables(elementName) {
          var pos = elementName.indexOf('_');
          var filterName = -1 === pos ? elementName : elementName.substr(0, pos);
          filter = $('#edit-' + filterName);
          filterFrom = $('#edit-' + filterName + '-from');
          filterTo = $('#edit-' + filterName + '-to');
        }

        var filters = ['beds', 'baths', 'rooms'];

        for (i = 0; i < filters.length; ++i) {
          $('#edit-' + filters[i]).change(function(event) {
            defineFilterVariables(event.target.name);
            if (filter.val()) {
              filterFrom.val('');
              filterTo.val('');
            }
          });

          $('#edit-' + filters[i] + '-from').change(function(event) {
            defineFilterVariables(event.target.name);
            if (filterFrom.val()) {
              filter.val('');
            }
          });

          $('#edit-' + filters[i] + '-to').change(function(event) {
            defineFilterVariables(event.target.name);
            if (filterTo.val()) {
              filter.val('');
            }
          });
        }
      });
    }
  };

})(jQuery);
