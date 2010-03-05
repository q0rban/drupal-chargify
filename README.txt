-----------------------------------------------------------------------------
Chargify module

This module creates Chargify database tables and views implementations for 
your Chargify subscriptions and customers. It creates Chargify customer to
Drupal user and Chargify subscription to Drupal user relationships. 

This module makes no assumptions about how your products or usage, so you 
will need to write your own module to interface with it. The Chargify Sites 
feature [0] is a good example of how you might go about this. Chargify sites 
is a module that allows a user to create site node and pay for that node 
using the Chargify and Chargify API modules.

Chargify module depends on the Chargify API module [1] 

[0] http://github.com/q0rban/chargify_sites
[1] http://drupal.org/project/chargify_api