function reiscout_editableaddress_entity_post_render_field(entity, field_name, field, reference) {
  if (field_name === 'field_address_text' && field.entity_type === 'node' && field.bundle === 'property' && reference.content.length && node_access(entity)) {
    //console.log(['reiscout_editableaddress_entity_post_render_field', entity, field_name, field, reference]);

    var display = field.display['default'];
    if (field.display['drupalgap']) {
      display = field.display['drupalgap'];
    }

    var label = '';
    if (display['label'] !== 'hidden') {
      label = '<div><h3>' + field.label + '</h3></div>';
    }

    // TODO: find a proper way to get a field value and render it
    var value = '';
    var default_lang = language_default();
    var language = entity.language;
    if (entity[field_name]) {
      var items = null;
      if (entity[field_name][default_lang]) {
        items = entity[field_name][default_lang];
        language = default_lang;
      }
      else if (entity[field_name][language]) {
        items = entity[field_name][language];
      }
      else if (entity[field_name]['und']) {
        items = entity[field_name]['und'];
        language = 'und';
      }

      if (items && typeof items[0] !== 'undefined') {
        if (typeof items[0].safe_value !== 'undefined') {
          value = items[0].safe_value;
        }
        else if (typeof items[0].value !== 'undefined') {
          value = items[0].value;
        }
      }
    }

    var content = [
      '<div class="' + field_name + '">',
        label,
        '<div class="editable-view">',
          '<span class="editable-value">',
            value,
          '</span>',
          '<span class="editable-control" style="margin-left: 10px;">',
            '<a class="ui-link ui-btn ui-btn-b ui-icon-edit ui-btn-icon-notext ui-btn-inline ui-shadow ui-corner-all editable-edit" role="button" onclick="_reiscout_editableaddress_edit_form_show(this); return false;">Edit</a>',
          '</span>',
         '</div>',
        '<div class="editable-form" style="display: none;">',
          '<input type="text" id="editable-form-value">',
          '<div class="editable-control" style="position: relative; float: right; right: -4px; top: -50px; z-index: 1000;">',
            '<a class="ui-link ui-btn ui-btn-b ui-icon-check ui-btn-icon-notext ui-btn-inline ui-shadow ui-corner-all editable-save" role="button" onclick="_reiscout_editableaddress_edit_form_save(this, ' + entity.nid +', \'' + field.bundle + '\', \'' + field_name + '\', \'' + language + '\'); return false;">Save</a>',
            '<a class="ui-link ui-btn ui-btn-b ui-icon-back ui-btn-icon-notext ui-btn-inline ui-shadow ui-corner-all editable-cancel" role="button" onclick="_reiscout_editableaddress_edit_form_cancel(this); return false;">Cancel</a>',
          '</div>',
        '</div>',
      '</div>'
    ].join('');

    reference.content = content;
  }
}

function _reiscout_editableaddress_edit_form_show(button) {
  var container = $(button).parent().parent().parent();
  container.find('#editable-form-value').val(container.find('.editable-view .editable-value').text());
  container.find('.editable-view, .editable-form').toggle();
}

function _reiscout_editableaddress_edit_form_save(button, nid, type, field, language) {
  var container = $(button).parent().parent().parent();
  var input     = container.find('#editable-form-value');
  var value     = input.val();

  if (value.length) {
    try {
      Drupal.services.call({
        method: 'POST',
        path: 'editableapi/save.json',
        service: 'editableapi',
        resource: 'save',
        data: JSON.stringify({
          nid: nid,
          type: type,
          field: field,
          language: language,
          delta: 0,
          value: value
        }),
        success: function(result) {
          //console.log(['editableapi.success', result]);

          container.find('.editable-view .editable-value').text(result.value);
          $('#node_' + nid + '_view_container h2:eq(0)').text(result.value);
          container.find('.editable-view, .editable-form').toggle();
          input.val('');
        },
        error: function(xhr, status, message) {
          //console.log(['editableapi.error', xhr, status, message]);

          if (message) {
            try {
              message = JSON.parse(message);
              if (typeof message === 'string') {
                drupalgap_alert(message);
              }
              else if (message instanceof Array) {
                drupalgap_alert(message.join("\n"));
              }
              else {
                drupalgap_alert('Unexpected error occurred');
              }
            }
            catch (error) {
              drupalgap_alert('Unexpected error occurred');
            }
          }
        }
      });
    }
    catch (error) {
      //console.log('_reiscout_editableaddress_edit_form_save - ' + error);

      container.find('.editable-view, .editable-form').toggle();
      input.val('');
    }
  }
  else {
    container.find('.editable-view, .editable-form').toggle();
    input.val('');
  }
}

function _reiscout_editableaddress_edit_form_cancel(button) {
  //console.log(['_reiscout_editableaddress_edit_form_cancel', arguments]);

  var container = $(button).parent().parent().parent();
  container.find('.editable-view, .editable-form').toggle();
  container.find('#editable-form-value').val('');
}
