
/**
 * Implements hook_form_alter().
 */
function reiscout_property_form_alter(form, form_state, form_id) {
    try {
        if (form_id == 'node_edit' && form.bundle == 'property') {
            // On property node edit forms, hide title field and set some non-empty value
            // In will be autopopulated on server side on save.
            form.elements['title'].prefix += '<div style="display: none;">';
            form.elements['title'].suffix += '</div>';
            form.elements['title'].default_value = 'value placeholder';
        }
    }
    catch (error) { console.log('reiscout_property_form_alter - ' + error); }
}
