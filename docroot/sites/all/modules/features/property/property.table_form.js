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

        // Attach events to filters
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

        // Attach events to CRM fields
        function showDlgMessagePropertyDeleted() {
          $('#jquery-dialog-message-property-deleted').dialog({
            modal: true,
            resizable: false,
            draggable: false,
            buttons: {
              Ok: function () {
                $(this).dialog('close');
              }
            }
          });
        }

        function showDlgMessage403() {
          $('#jquery-dialog-message-403').dialog({
            modal: true,
            resizable: false,
            draggable: false,
            buttons: {
              Ok: function () {
                $(this).dialog('close');
              }
            }
          });
        }

        function createElementForField(field, value) {
          var el;

          if ('last-contacted' === field) {
            el = document.createElement('input');
            el.type = 'date';
            el.value = value;
            el.className = 'form-text';
          }
          else {
            el = document.createElement('select');
            el.appendChild(new Option('- None -', '0'));
            for (const [value, text] of fieldLeadStatusAllowedValues) {
              el.appendChild(new Option(text, value));
            }
            el.value = value;
            el.className = 'form-select';
          }

          return el;
        }

        function displayElementForField(field, eventObject) {
          var nid = eventObject.closest('.crm-fields').id.substr(11);
          var divValue = $(eventObject).closest('.field').find('.value');
          var divIcon = $(eventObject);

          $.ajax({
            url: '/property/' + nid + '/field/' + field + '/get-value',
            dataType: 'json',
            success: function (data) {
              if (data.success) {
                var el = createElementForField(field, data.value);
                divValue.html(el);
                divIcon.removeClass('edit').addClass('save');
                divIcon.off('click').click(function () {
                  saveValueOfField(field, this);
                });
              }
              else {
                showDlgMessagePropertyDeleted();
              }
            },
            statusCode: {
              403: showDlgMessage403
            },
          });
        }

        function saveValueOfField(field, eventObject) {
          var nid = eventObject.closest('.crm-fields').id.substr(11);
          var divValue = $(eventObject).closest('.field').find('.value');
          var value = divValue.children().val();
          var divIcon = $(eventObject);

          $.ajax({
            url: '/property/' + nid + '/field/' + field + '/save-value',
            data: {value: value},
            type: 'POST',
            dataType: 'json',
            success: function (data) {
              if (data.success) {
                divValue.html(data.value);
                divIcon.removeClass('save').addClass('edit');
                divIcon.off('click').click(function () {
                  displayElementForField(field, this);
                });
              }
              else {
                showDlgMessagePropertyDeleted();
              }
            },
            statusCode: {
              403: showDlgMessage403
            },
          });
        }

        $('.last-contacted .icon.edit').click(function () {
          displayElementForField('last-contacted', this);
        });

        $('.lead-status .icon.edit').click(function () {
          displayElementForField('lead-status', this);
        });
      });
    }
  };

})(jQuery);
