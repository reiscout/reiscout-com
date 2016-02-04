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

      // Hide some fields fro now
      var hide_fields = [
        'field_owner_fname', 'field_owner_lname', 'field_owner_phone', 'field_owner_address'
      ];
      for (var i in hide_fields) {
        var fieldname = hide_fields[i];
        if (form.elements[fieldname]) {
          form.elements[fieldname].prefix = '<div style="display: none;">';
          form.elements[fieldname].suffix = '</div>';
        }
      }
    }
  }
  catch (error) {
    console.log('reiscout_property_form_alter - ' + error);
  }
}

/**
 * Implements hook_menu().
 */
function reiscout_property_menu() {
  var items = {};
  items['property-listing'] = {
    title: 'Reiscout',
    page_callback: 'reiscout_property_listing_page'
  };

  items['my-properties'] = {
    title: 'My Properties',
    page_callback: 'reiscout_property_my_properties_view_page'
  };


  return items;
}

/**
 * The page callback to display the view.
 */
function reiscout_property_listing_page() {
  try {
    var content = {};
    content['reiscout_property_listing'] = {
      theme: 'view',
      format: 'unformatted_list',
      path: 'drupalgap/views_datasource/property-listing', /* the path to the view in Drupal */
      row_callback: 'reiscout_property_listing_row',
      empty_callback: 'reiscout_property_listing_empty',
      attributes: {
        id: 'reiscout_property_listing_view'
      }
    };
    return content;
  }
  catch (error) {
    console.log('reiscout_property_listing_page - ' + error);
  }
}

/**
 * The row callback to render a single row.
 */
function reiscout_property_listing_row(view, row) {
  try {
    if (row.image.src) {
      var row_html = '';
      row_html += '<img src="' + row.image.src + '">';
      if (row.address && row.address.length) {
        row_html += '<div class="address">' + row.address + '</div>';
      }
      row_html = l(row_html, 'node/' + row.nid);
      return '<div class="view-row">' + row_html + '</div>';
    }
  }
  catch (error) {
    console.log('reiscout_property_listing_row - ' + error);
  }
}

/**
 * Shows empty view content
 */
function reiscout_property_listing_empty(view) {
  try {
    return t('Sorry, no property objects were found.');
  }
  catch (error) {
    console.log('reiscout_property_listing_empty - ' + error);
  }
}

/**
 * The page callback to display the view.
 */
function reiscout_property_my_properties_view_page() {
  try {
    var content = {};

    content['reiscout_my_properties_listing'] = {
      theme: 'view',
      format: 'unformatted_list',
      path: 'drupalgap/views_datasource/my-properties/' + Drupal.user.uid, /* the path to the view in Drupal */
      row_callback: 'reiscout_property_listing_row',
      empty_callback: 'reiscout_property_my_properties_view_empty',
      attributes: {
        id: 'reiscout_property_my_properties_view'
      }
    };
    return content;
  }
  catch (error) {
    console.log('reiscout_property_my_properties_view_page - ' + error);
  }
}

/**
 * Shows empty view content
 */
function reiscout_property_my_properties_view_empty(view) {
  try {
    return t('You are not added any property objects yet.');
  }
  catch (error) {
    console.log('reiscout_property_my_properties_view_empty - ' + error);
  }
}
