<?php
// $Id: chargify_handler_field_product_name.inc,v 1.1 2010/03/05 21:01:12 q0rban Exp $

/**
 * @file
 * Contains the Chargify product name field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to a node.
 */
class chargify_handler_field_product_name extends views_handler_field {
  function render($values) {
    $name = '';
    if ($product = chargify_api_product_get($values->{$this->field_alias}, 'handle')) {
      $name = t($product->getName());
    }
    return $name;
  }
}
