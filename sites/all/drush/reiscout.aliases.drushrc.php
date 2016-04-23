<?php

$aliases['local'] = array(
  'root' => '/var/www/drupalvm/reiscout-com',
  'uri'  => 'http://reiscout.dev',
  'path-aliases' => array(
    '%dump-dir' => '/tmp',
  ),
  'command-specific' => array (
    'sql-sync' => array (
      'simulate' => '0',
    ),
    'rsync' => array (
      'simulate' => '0',
    ),
  ),
);

$aliases['live'] = array (
  'uri' => 'http://reiscout.com',
  'root' => '/home/reiscout/www',
  'remote-user' => 'reiscout',
  'remote-host' => 'a2ss24.a2hosting.com',
  'ssh-options'  => '-p 7822',  // To change the default port on remote server
  'path-aliases' => array(
    '%dump-dir' => '/tmp',
  ),
  'source-command-specific' => array (
    'sql-sync' => array (
      'no-cache' => TRUE,
      'structure-tables-key' => 'common',
    ),
  ),
  // No need to modify the following settings
  'command-specific' => array (
    'rsync' => array (
      'simulate' => '1',
    ),
    'sql-sync' => array (
      'simulate' => '1',
      'sanitize' => TRUE,
      'no-ordered-dump' => TRUE,
      'structure-tables' => array(
       // You can add more tables which contain data to be ignored by the database dump
        'common' => array('cache', 'cache_filter', 'cache_menu', 'cache_page', 'history', 'sessions', 'watchdog'),
      ),
    ),
  ),
);
