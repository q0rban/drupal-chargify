<?php
// $Id: chargify.theme.inc,v 1.1 2010/03/05 21:01:12 q0rban Exp $

/**
 * @file
 *   Theme callbacks and preprocess functions.
 */

/**
 * Theme callback to return a chargify state
 */
function theme_chargify_subscription_state($state = '') {
  if ($label = chargify_subscription_state($state)) {
    return "<div class='chargify-state chargify-state-$state'>$label</div>";
  }
}

/**
 * Theme callback to return a product price.
 */
function theme_chargify_product_price($product) {
  if (is_object($product)) {
    $denom = '<span class="denom">$</span>';
    $price = $product->getPriceInDollars();
    $divider = t('per');
    $interval = $product->getIntervalUnit();

    $output = "<div class='chargify-product-price'>";
    $output .= "<span class='price'>{$denom}{$price}</span>";
    $output .= "&nbsp;<span class='divider'>$divider</span>";
    $output .= "&nbsp;<span class='interval'>$interval</span>";
    $output .= "</div>";

    return $output;
  }
}