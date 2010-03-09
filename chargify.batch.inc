<?php
// $Id: chargify.batch.inc,v 1.2 2010/03/09 17:30:33 q0rban Exp $

/**
 * @file
 *   Holds all batch processing for the Post back hook.
 *
 * @see chargify_api_chargify_postback() && chargify_chargify_api_postback().
 */

/**
 * Batch operation to update a single subscription.
 *
 * @param $subscription_id
 *   The numeric ID of the Chargify subscription.
 * @param $context
 *   The batch context array.
 */
function chargify_subscription_update_batch_op($subscription_id, &$context) {
  $context['message'] = t('Updating Chargify subscription #%subscription_id', array('%subscription_id' => $subscription_id));
  $context['results'][$subscription_id] = chargify_subscription_update($subscription_id);
}

/**
 * Update a single subscription by ID.
 *
 * @param $subscription_id
 *   The Chargify ID of the subscription.
 * @return
 *   Boolean success.
 */
function chargify_subscription_update($subscription_id) {
  if ($subscription = chargify_api_subscription_get($subscription_id)) {
    chargify_subscription_save_record($subscription);
    return TRUE;
  }
  return FALSE;
}

/**
 * Batch completion callback
 */
function chargify_subscription_update_batch_finished($success, $results, $ops) {
  if ($success) {
    // The results come in as an array keyed by the subscription ID, with a boolean 
    // value to specify if any updates were made.
    $ids = array_keys($results, TRUE);
    $count = count($ids);
    $args = array('@count' => $count, '%subscription_ids' => implode(', ', $ids));
    // Were any subscriptions updated?
    if ($count) {
      $singular = 'subscription #%subscription_ids was updated.';
      $plural = '@count subscriptions were updated, with the following IDs: %subscription_ids';
      $message = format_plural($count, $singular, $plural, $args);
      $severity = WATCHDOG_NOTICE;
    }
    // If not, throw a warning.
    else {
      $args['%subscription_ids'] = implode(', ', array_keys($results));
      $message = t('A Chargify postback was attempted, but no subscriptions were updated. The subscription ID(s) that were attempted to update were as follows: %subscription_ids', $args);
      $severity = WATCHDOG_WARNING;
    }
    watchdog('chargify', $message, NULL, $severity);
  }
  else {
    $error_op = reset($ops);
    $message = 'An error occurred while processing subscription #%subscription_id.';
    watchdog('chargify', $message, array('%subscription_id' => print_r($error_op, 1)), WATCHDOG_ERROR);
  }
}