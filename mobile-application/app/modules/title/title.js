/**
 * Implements hook_form_alter().
 */
function title_form_alter(form, form_state, form_id) {
  try {
    // On node edit forms, if there is a title field, hide the normal node title
    // element and have it be auto populated with the value entered into the
    // title field.
    if (form_id == 'node_edit' && form.elements['title_field']) {
      var language = form.elements.language.default_value;
      form.elements['title'].prefix += '<div style="display: none;">';
      form.elements['title'].suffix += '</div>';
      form.elements['title_field'][language][0].options.attributes.onchange = "title_field_onchange(this, '" + form.elements.title.options.attributes.id + "')";
    }
  }
  catch (error) { console.log('title_form_alter - ' + error); }
}

/**
 *
 */
function title_field_onchange(input, id) {
  try {
    $('#' + id).val($(input).val());
  }
  catch (error) { console.log('title_field_onchange - ' + error); }
}
