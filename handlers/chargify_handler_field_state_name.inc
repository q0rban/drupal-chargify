<?php
// $Id$

/**
 * @file
 * Contains the Chargify product name field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to a node.
 */
class chargify_handler_field_state_name extends views_handler_field {
  function render($values) {
    return theme('chargify_subscription_state', $values->{$this->field_alias});
  }
}
