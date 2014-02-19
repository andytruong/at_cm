<?php
/**
 * @file at_cm.hooks.inc
 */

/**
 * Implements hook_init()
 */
function at_cm_init() {
    if ($api_key = variable_get('at_cm.api_key', '')) {
        at_container('container')->offsetSet('cm.null', '');
        at_container('container')->offsetSet('cm.auth', $api_key);
    }
}
