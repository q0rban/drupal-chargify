<?php
// $Id$

/**
 * @file
 *   Interface between chargify_subscriptions.module and views.module.
 */

/**
 * Implementation of hook_views_data().
 */
function chargify_views_data() {
  $data['chargify_subscriptions']['table']['group'] = t('Chargify Subscriptions');

  $data['chargify_subscriptions']['table']['base'] = array(
    'field' => 'subscription_id',
    'title' => t('Chargify Subscriptions'),
    'help' => t("Example table contains example content and can be related to nodes."),
    'weight' => -10,
  );

  $data['chargify_subscriptions']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  $data['chargify_subscriptions']['uid'] = array(
    'title' => t('Chargify Subscription'),
    'help' => t('Subscriptions for a particular user.'),
    'relationship' => array(
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('Chargify Subscription'),
    ),
  );

  $data['chargify_subscriptions']['state'] = array(
    'title' => t('Subscription state (machine)'),
    'help' => t('The machine name state of the subscription within Chargify.'),
    'field' => array(
      'title' => t('State (machine)'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['chargify_subscriptions']['state_name'] = array(
    'title' => t('Subscription state'),
    'help' => t('The state of the subscription within Chargify.'),
    'real field' => 'state',
    'field' => array(
      'title' => t('State'),
      'handler' => 'chargify_handler_field_state_name',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['chargify_subscriptions']['product_handle'] = array(
    'title' => t('Product handle'),
    'help' => t('The product handle within Chargify.'),
    'field' => array(
      'title' => t('Product handle'),
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['chargify_subscriptions']['product_name'] = array(
    'title' => t('Product'),
    'help' => t('The product name within Chargify.'),
    'real field' => 'product_handle',
    'field' => array(
      'title' => t('Product'),
      'handler' => 'chargify_handler_field_product_name',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'chargify_handler_sort_product_name',
    ),
  );

  $data['chargify_subscriptions']['subscription_id'] = array(
    'title' => t('Subscription ID'),
    'help' => t('Numeric ID of the subscription.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['chargify_customers']['table']['group'] = t('Chargify Customers');

  $data['chargify_customers']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  $data['chargify_customers']['customer_id'] = array(
    'title' => t('Customer ID'),
    'help' => t('Numeric ID of the Chargify customer.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
     ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function chargify_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'chargify') .'/handlers',
    ),
    'handlers' => array(
      // field handlers
      'chargify_handler_field_product_name' => array(
        'parent' => 'views_handler_field',
      ),
      'chargify_handler_field_state_name' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}