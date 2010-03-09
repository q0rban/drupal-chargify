<?php
// $Id: chargify.batch.inc,v 1.2 2010/03/09 17:30:33 q0rban Exp $

/**
 * @file
 *   Holds all batch processing for the Post back hook.
 *
 * @see chargify_api_chargify_postback() && chargify_chargify_api_postback().
 */

/**
 * Batch operation to update a single customer.
 *
 * @param $customer_id
 *   The numeric ID of the Chargify customer.
 * @param $context
 *   The batch context array.
 */
function chargify_customer_update_batch_op($customer_id, &$context) {
  $context['message'] = t('Updating Chargify customer #%customer_id', array('%customer_id' => $customer_id));
  $context['results'][$customer_id] = chargify_customer_update($customer_id);
}

/**
 * Update a single customer by ID.
 */
function chargify_customer_update($customer_id) {
  if ($subscriptions = chargify_api_customer_get_subscriptions($customer_id)) {
    if (!empty($subscriptions)) {
      foreach ($subscriptions as $subscription) {
        chargify_subscription_save_record($subscription);
      }
    }
    return TRUE;
  }
  return FALSE;
}

/**
 * Batch completion callback
 */
function chargify_customer_update_batch_finished($success, $results, $ops) {
  if ($success) {
    // The results come in as an array keyed by the Customer ID, with a boolean 
    // value to specify if any updates were made.
    $ids = array_keys($results, TRUE);
    $count = count($ids);
    $args = array('@count' => $count, '%customer_ids' => implode(', ', $ids));
    // Were any customers updated?
    if ($count) {
      $singular = 'Customer #%customer_ids was updated.';
      $plural = '@count Customers were updated, with the following IDs: %customer_ids';
      $message = format_plural($count, $singular, $plural, $args);
      $severity = WATCHDOG_NOTICE;
    }
    // If not, throw a warning.
    else {
      $args['%customer_ids'] = implode(', ', array_keys($results));
      $message = t('A Chargify postback was attempted, but no customers were updated. The customer ID(s) that were attempted to update were as follows: %customer_ids', $args);
      $severity = WATCHDOG_WARNING;
    }
    watchdog('chargify', $message, NULL, $severity);
  }
  else {
    $error_op = reset($ops);
    $message = 'An error occurred while processing customer #%customer_id.';
    watchdog('chargify', $message, array('%customer_id' => print_r($error_op, 1)), WATCHDOG_ERROR);
  }
}