<?php
/**
 * @file at_cm.rules.inc
 *
 * Rules integration.
 */

/**
 * Implements hook_rules_action_info()
 */
function at_cm_rules_action_info() {
  return array(
    'at_cm_subscribers_add' => array(
      'group' => t('CampaignMonitor'),
      'label' => t('Add a contact to a list'),
      'parameter' => array(
        'list_ids' => array(
          'type' => 'list<text>',
          'label' => t('List ID'),
          'options list' => 'at_cm_lists_options',
          'optional' => FALSE,
        ),
        'email' => array(
          'type' => 'text',
          'label' => t('Email'),
          'description' => t('Email address of contact'),
          'optional' => FALSE,
        ),
        'name' => array(
          'type' => 'text',
          'label' => t('Name'),
          'description' => t('Full name of contact'),
          'optional' => TRUE,
        ),
      ),
      'base' => 'at_cm_action_subscribers_add',
      'access callback' => 'rules_system_integration_access',
    ),
    // unsubscribe
  );
}

function at_cm_action_subscribers_add($list_ids, $email, $name) {
    $service_subscriber = AT_CM::getSubscribers();

    foreach ($list_ids as $list_id) {
        $service_subscriber->set_list_id($list_id);
        $response = $service_subscriber->add($subscriber = array(
             'EmailAddress' => $email,
             'Name' => filter_xss_admin($name),
        ));

        if ($response->http_status_code == 201) {
            watchdog(
              'at_cm',
              'Subcribed %mail to %list',
              array('%mail' => $email, '%list' => $list_id),
              WATCHDOG_INFO
            );
        }
        else {
            watchdog(
              'at_cm',
              'Failed to subcribed %mail to %list',
              array('%mail' => $email, '%list' => $list_id),
              WATCHDOG_ERROR
            );
        }
    }
}
