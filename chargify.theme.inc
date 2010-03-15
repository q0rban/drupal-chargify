<?php
// $Id: chargify.theme.inc,v 1.2 2010/03/15 15:45:23 q0rban Exp $

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
    $default = '<span class="price"><span class="denom">@denom</span>@price</span> <span class="divider">every</span>';
    $singular = $default .' <span class="interval">@interval-unit</span>';
    $plural = $default .' <span class="interval">@interval-num @interval-units</span>';

    $args = array(
      '@denom' => '$',
      '@price' => $product->getPriceInDollars(),
      '@interval-num' => $product->getInterval(),
      '@interval-unit' => $product->getIntervalUnit(),
    );

    $text = format_plural($product->getInterval(), $singular, $plural, $args);

    return "<div class='chargify-product-price'>$text</div>";
  }
}