<?php

/**
 * Implements hook_drush_command().
 *
 * Register the entityreference prune command(s)
 */
function entityreference_prune_drush_command() {
  $commands = array();

  $commands['entityreference-prune'] = array(
    'callback' => 'drush_entityreference_prune',
    'description' => 'Prune duplicate entity references',
    'aliases' => array('erp'),
    'examples' => array(
      'drush entityreference_prune field_name' => 'Prune duplicates in a certain field',
    ),
    'arguments' => array(
      'field_name' => 'The field name to scan',
    ),
    'required-arguments' => 1,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  return $commands;
}

function drush_entityreference_prune($field_name) {

  // check if the field exists
  $info = field_info_field($field_name);
  if ($info) {

    $data = 'field_data_' . $field_name;
    $field = $field_name . '_target_id';

    $results = db_query('SELECT entity_id, ' . $field . ', COUNT(' . $field . ') AS c
      FROM ' . $data . ' GROUP BY entity_id, ' . $field);

    while ($result = $results->fetchAssoc()) {

      if ($result['c'] > 1) {

        $limit = intval($result['c']) - 1;
        db_query('DELETE FROM ' . $data . ' WHERE entity_id=' . intval($result['entity_id']) . ' AND ' . $field . '=' . intval($result[$field]) . ' LIMIT ' . $limit);
        drush_log('Cleaned duplicates for entity_id: ' . $result['entity_id'] . ' target_id:' . $result[$field], 'ok');

      }

    }

  }

}
