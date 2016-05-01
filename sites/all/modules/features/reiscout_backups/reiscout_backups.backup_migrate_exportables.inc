<?php
/**
 * @file
 * reiscout_backups.backup_migrate_exportables.inc
 */

/**
 * Implements hook_exportables_backup_migrate_destinations().
 */
function reiscout_backups_exportables_backup_migrate_destinations() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'manual';
  $item->name = 'Manual Backups Directory';
  $item->subtype = 'file_manual';
  $item->location = 'private://backup_migrate/manual';
  $item->settings = array(
    'chmod' => '0660',
    'chgrp' => '',
  );
  $export['manual'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'nodesquirrel';
  $item->name = 'NodeSquirrel Free 14 backups Daily';
  $item->subtype = 'nodesquirrel';
  $item->location = '';
  $item->settings = array(
    'secret_key' => '9e7396b98c9a04fe0a9b7fe78cda6a77:3a19598f1cecd5b58617868f773eaeae',
    'location' => '',
  );
  $export['nodesquirrel'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'scheduled';
  $item->name = 'Scheduled Backups Local Daily';
  $item->subtype = 'file_scheduled';
  $item->location = 'private://backup_migrate/scheduled/daily';
  $item->settings = array(
    'chmod' => '0660',
    'chgrp' => '',
  );
  $export['scheduled'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'scheduled_backups_directory_monthly';
  $item->name = 'Scheduled Backups Local Monthly';
  $item->subtype = 'file';
  $item->location = 'private://backup_migrate/scheduled/monthly';
  $item->settings = array(
    'chmod' => '0660',
    'chgrp' => '',
  );
  $export['scheduled_backups_directory_monthly'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'scheduled_backups_directory_weekly';
  $item->name = 'Scheduled Backups Local Weekly';
  $item->subtype = 'file';
  $item->location = 'private://backup_migrate/scheduled/weekly';
  $item->settings = array(
    'chmod' => '0660',
    'chgrp' => '',
  );
  $export['scheduled_backups_directory_weekly'] = $item;

  return $export;
}

/**
 * Implements hook_exportables_backup_migrate_profiles().
 */
function reiscout_backups_exportables_backup_migrate_profiles() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'no_cache';
  $item->name = 'no cache';
  $item->filename = '[site:name]';
  $item->append_timestamp = TRUE;
  $item->timestamp_format = 'Y-m-d\\TH-i-s';
  $item->filters = array(
    'compression' => 'gzip',
    'notify_success_enable' => 0,
    'notify_success_email' => 'info@reiscout.com',
    'notify_failure_enable' => 1,
    'notify_failure_email' => 'info@reiscout.com',
    'utils_site_offline' => 0,
    'utils_site_offline_message' => 'Real Estate Investment Scout is currently under maintenance. We should be back shortly. Thank you for your patience.',
    'utils_description' => '',
    'use_cli' => 0,
    'ignore_errors' => 0,
    'sources' => array(
      'db' => array(
        'exclude_tables' => array(),
        'nodata_tables' => array(
          'driq_cache' => 'driq_cache',
          'driq_cache_admin_menu' => 'driq_cache_admin_menu',
          'driq_cache_block' => 'driq_cache_block',
          'driq_cache_bootstrap' => 'driq_cache_bootstrap',
          'driq_cache_features' => 'driq_cache_features',
          'driq_cache_field' => 'driq_cache_field',
          'driq_cache_filter' => 'driq_cache_filter',
          'driq_cache_form' => 'driq_cache_form',
          'driq_cache_image' => 'driq_cache_image',
          'driq_cache_libraries' => 'driq_cache_libraries',
          'driq_cache_mailchimp' => 'driq_cache_mailchimp',
          'driq_cache_menu' => 'driq_cache_menu',
          'driq_cache_page' => 'driq_cache_page',
          'driq_cache_panels' => 'driq_cache_panels',
          'driq_cache_path' => 'driq_cache_path',
          'driq_cache_path_breadcrumbs' => 'driq_cache_path_breadcrumbs',
          'driq_cache_rules' => 'driq_cache_rules',
          'driq_cache_token' => 'driq_cache_token',
          'driq_cache_update' => 'driq_cache_update',
          'driq_cache_views' => 'driq_cache_views',
          'driq_cache_views_data' => 'driq_cache_views_data',
        ),
        'utils_lock_tables' => 0,
      ),
      'files' => array(
        'exclude_filepaths' => 'backup_migrate
styles
css
js
ctools
less',
      ),
      'archive' => array(
        'exclude_filepaths' => 'public://backup_migrate
public://styles
public://css
public://js
public://ctools
public://less
private://backup_migrate
sites/default/settings.php
/tmp',
      ),
    ),
  );
  $export['no_cache'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'no_compression';
  $item->name = 'no compression, cache, logs and etc ';
  $item->filename = 'RealEstateInvestmentScout';
  $item->append_timestamp = TRUE;
  $item->timestamp_format = 'Y-m-d\\TH-i-s';
  $item->filters = array(
    'compression' => 'none',
    'notify_success_enable' => 0,
    'notify_success_email' => 'bbaeta@hotmail.com',
    'notify_failure_enable' => 0,
    'notify_failure_email' => 'bbaeta@hotmail.com',
    'utils_site_offline' => 0,
    'utils_site_offline_message' => 'Real Estate Investment Scout is currently under maintenance. We should be back shortly. Thank you for your patience.',
    'utils_description' => '',
    'use_cli' => 0,
    'ignore_errors' => 0,
    'sources' => array(
      'db' => array(
        'exclude_tables' => array(),
        'nodata_tables' => array(
          'driq_cache' => 'driq_cache',
          'driq_cache_admin_menu' => 'driq_cache_admin_menu',
          'driq_cache_block' => 'driq_cache_block',
          'driq_cache_bootstrap' => 'driq_cache_bootstrap',
          'driq_cache_features' => 'driq_cache_features',
          'driq_cache_field' => 'driq_cache_field',
          'driq_cache_filter' => 'driq_cache_filter',
          'driq_cache_form' => 'driq_cache_form',
          'driq_cache_image' => 'driq_cache_image',
          'driq_cache_libraries' => 'driq_cache_libraries',
          'driq_cache_mailchimp' => 'driq_cache_mailchimp',
          'driq_cache_menu' => 'driq_cache_menu',
          'driq_cache_page' => 'driq_cache_page',
          'driq_cache_panels' => 'driq_cache_panels',
          'driq_cache_path' => 'driq_cache_path',
          'driq_cache_path_breadcrumbs' => 'driq_cache_path_breadcrumbs',
          'driq_cache_rules' => 'driq_cache_rules',
          'driq_cache_token' => 'driq_cache_token',
          'driq_cache_update' => 'driq_cache_update',
          'driq_cache_views' => 'driq_cache_views',
          'driq_cache_views_data' => 'driq_cache_views_data',
          'driq_captcha_points' => 'driq_captcha_points',
          'driq_sessions' => 'driq_sessions',
          'driq_watchdog' => 'driq_watchdog',
        ),
        'utils_lock_tables' => 0,
      ),
      'files' => array(
        'exclude_filepaths' => 'backup_migrate
styles
css
js
ctools
less',
      ),
      'archive' => array(
        'exclude_filepaths' => 'public://backup_migrate
public://styles
public://css
public://js
public://ctools
public://less
private://backup_migrate
sites/default/settings.php
/tmp',
      ),
    ),
  );
  $export['no_compression'] = $item;

  return $export;
}

/**
 * Implements hook_exportables_backup_migrate_schedules().
 */
function reiscout_backups_exportables_backup_migrate_schedules() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'daily_backup_to_local';
  $item->name = 'DB & Code & Files to Server Daily';
  $item->source_id = 'archive';
  $item->destination_id = 'scheduled';
  $item->copy_destination_id = '';
  $item->profile_id = 'no_cache';
  $item->keep = -2;
  $item->period = 86400;
  $item->enabled = TRUE;
  $item->cron = 'builtin';
  $item->cron_schedule = '0 4 * * *';
  $export['daily_backup_to_local'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'db_code_files_to_server_monthly';
  $item->name = 'DB & Code & Files to Server Monthly';
  $item->source_id = 'archive';
  $item->destination_id = 'scheduled_backups_directory_monthly';
  $item->copy_destination_id = '';
  $item->profile_id = 'no_cache';
  $item->keep = 0;
  $item->period = 2419200;
  $item->enabled = TRUE;
  $item->cron = 'builtin';
  $item->cron_schedule = '0 4 * * *';
  $export['db_code_files_to_server_monthly'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'db_code_files_to_server_weekly';
  $item->name = 'DB & Code & Files to Server Weekly';
  $item->source_id = 'archive';
  $item->destination_id = 'scheduled_backups_directory_weekly';
  $item->copy_destination_id = '';
  $item->profile_id = 'no_cache';
  $item->keep = 0;
  $item->period = 604800;
  $item->enabled = TRUE;
  $item->cron = 'builtin';
  $item->cron_schedule = '0 4 * * *';
  $export['db_code_files_to_server_weekly'] = $item;

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'nodesquirrel';
  $item->name = 'DB & Code & Files to NodeSquirrel Daily';
  $item->source_id = 'archive';
  $item->destination_id = 'nodesquirrel';
  $item->copy_destination_id = '';
  $item->profile_id = 'default';
  $item->keep = -2;
  $item->period = 86400;
  $item->enabled = TRUE;
  $item->cron = 'builtin';
  $item->cron_schedule = '0 4 * * *';
  $export['nodesquirrel'] = $item;

  return $export;
}
