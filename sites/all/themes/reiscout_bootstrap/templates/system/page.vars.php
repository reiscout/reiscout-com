<?php
/**
 * @file
 * Stub file for "page" theme hook [pre]process functions.
 */

/**
 * Pre-processes variables for the "page" theme hook.
 *
 * See template for list of available variables.
 *
 * @see page.tpl.php
 *
 * @ingroup theme_preprocess
 */
function reiscout_bootstrap_preprocess_page(&$variables) {
    $sign_in_block = user_block_view('login');
    if ($sign_in_block) {
        $sign_in_block['content']['actions']['#weight'] = 9;
        $sign_in_block['content']['links']['#weight'] = 10;
        $variables['login_block'] = $sign_in_block;
    }
}
