<?php
// $Id: chargify.batch.inc,v 1.1 2010/03/08 20:38:34 q0rban Exp $

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
  $context['results'][] = $customer_id;
  chargify_customer_update($customer_id);
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
  }
}

/**
 * Batch completion callback
 */
function chargify_customer_update_batch_finished($success, $results, $ops) {
  if ($success) {
    watchdog('chargify', $message);
  }
  else {
    $error_op = reset($ops);
    $message = 'An error occurred while processing customer #%customer_id.';
    watchdog('chargify', $message, array('%customer_id' => $error_op), WATCHDOG_ERROR);
  }
}