<?php
/**
 * @file
 * reiscout_blog.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function reiscout_blog_filter_default_formats() {
  $formats = array();

  // Exported format: Blog Article.
  $formats['blog_article'] = array(
    'format' => 'blog_article',
    'name' => 'Blog Article',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_htmlcorrector' => array(
        'weight' => 10,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
