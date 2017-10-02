<?php

/**
 * @file
 * User page callback file for the Reiscout Points User Balance module.
 */

/**
 * Page callback; Displays a user's current balance in Reiscout points.
 */
function reiscout_points_user_balance_page($uid) {
  $content = array();

  $amount = reiscout_points_user_balance_get($uid);
  $t_args = array(
    '!amount' => $amount,
    '!our_prices_page_url' => url('our-prices'),
  );

  $content['reiscout-points-user-balance'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'id' => 'reiscout-points-user-balance',
    ),
  );

  $content['reiscout-points-user-balance']['current-state'] = array(
    '#prefix' => '<div class="current-state">',
    '#markup' => format_plural($amount, 'You have 1 point', 'You have !amount points', $t_args),
    '#suffix' => '</div >',
  );

  $content['reiscout-points-user-balance']['description'] = array(
    '#prefix' => '<div class="description">',
    '#markup' => t('Points may be used for the purchase of any <a href="!our_prices_page_url">product (service)</a> within our site.', $t_args),
    '#suffix' => '</div >',
  );

  $content['reiscout-points-user-balance']['buy-more-points-link'] = array(
    '#prefix' => '<div class="buy-points-link">',
    '#markup' => l(t('Buy more points'), 'reiscout-points/buy/10', array('query' => array('return_to' => $_GET['q']))),
    '#suffix' => '</div >',
  );

  $content['reiscout-points-user-balance']['buy-points-package-link'] = array(
    '#prefix' => '<div class="buy-points-link">',
    '#markup' => l(t('Buy a points package'), 'reiscout-points/buy', array('query' => array('return_to' => $_GET['q']))),
    '#suffix' => '</div >',
  );

  return $content;
}
