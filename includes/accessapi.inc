<?php

/**
 * @file
 * Access API.
 *
 *
 *  Copyright 2019-2020 Leiden University Library
 *
 *  This file is part of islandora_handled_datastream_access.
 *
 *  islandora_handled_datastream_access is free software: you can redistribute
 *  it and/or modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation, either version 3 of the License,
 *  or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/**
 * Response in JSON about access for specific datastream of an object identified by a handle.
 *
 * See islandora_handled_datastream_access_json_access_object for specifics
 *
 * @param string $handleprefix
 *   The handle prefix.
 *
 * @param string $handlesuffix
 *   The handle suffix.
 *
 * @param string $dsid
 *   A id of a (existing?) datastream.
 */
function islandora_handled_datastream_access_json_access_handle($handleprefix, $handlesuffix, $neededdatastream) {
  $object = islandora_handled_datastream_access_object_load_handle($handleprefix . '/' . $handlesuffix);

  islandora_handled_datastream_access_json_access_object($object, $neededdatastream);
}

/**
 * Response in JSON about access for specific datastream of an object.
 *
 * Creates a JSON response that can have the following format:
 *  Access allowed -> Status: 200 OK, content: { 'pid' => $pid, 'dsid' => $dsid, 'access' => true }
 *  Access forbidden -> Status: 403 Forbidden, content: { 'pid' => $pid, 'dsid' => $dsid, 'access' => false, 'reason' => 'Forbidden' }
 *  Object not found -> Status: 404 Not Found, content: { 'pid' => $pid, 'dsid' => $dsid, 'access' => false, 'reason' => 'Object not found' }
 *  Datastream not found -> Status: 404 Not Found, content: { 'pid' => $pid, 'dsid' => $dsid, 'access' => false, 'reason' => 'Datastream not found' }
 *
 * @param $object
 *   An object or NULL.
 *
 * @param string $dsid
 *   A id of a (existing?) datastream.
 */
function islandora_handled_datastream_access_json_access_object($object, $neededdatastream) {
  $pid = $object ? $object->id : NULL;
  $dsid = $object ? _islandora_handled_datastream_access_get_dsid($object, $neededdatastream) : NULL;

  if (!isset($object)) {
    _islandora_handled_datastream_access_json_response('404 Not Found', array('pid' => $pid, 'dsid' => $dsid, 'access' => FALSE, 'reason' => t('Object not found')));
  }
  if (!isset($object[$dsid])) {
    _islandora_handled_datastream_access_json_response('404 Not Found', array('pid' => $pid, 'dsid' => $dsid, 'access' => FALSE, 'reason' => t('Datastream not found')));
  }
  $datastream = $object[$dsid];

  $canaccess = _islandora_handled_datastream_access_get_access('islandora_datastream_access', ISLANDORA_VIEW_OBJECTS, $datastream);

  if ($canaccess) {
    _islandora_handled_datastream_access_json_response('200 OK', array('pid' => $pid, 'dsid' => $dsid, 'access' => $canaccess));
  }
  else {
    _islandora_handled_datastream_access_json_response('403 Forbidden', array('pid' => $pid, 'dsid' => $dsid, 'access' => $canaccess, 'reason' => t('Forbidden')));
  }
}

/**
 * Helper function the determine the access of a specific thing.
 */
function _islandora_handled_datastream_access_get_access($accessfunc, $op, $thing) {
  global $user;
  $doimpersonate = FALSE;
  // Impersonate an anonymous user:
  if ($doimpersonate) {
    $original_user = $user;
    $old_state = drupal_save_session();
    drupal_save_session(FALSE);
    $user = drupal_anonymous_user();
  }
  // Check the access.
  $canaccess = call_user_func($accessfunc, $op, $thing, $user);

  // Stop impersonating...
  if ($doimpersonate) {
    $user = $original_user;
    drupal_save_session($old_state);
  }

  return $canaccess;
}

/**
 * Helper function to write out a JSON response.
 */
function _islandora_handled_datastream_access_json_response($status, $data = NULL) {
  drupal_add_http_header('Status', $status);
  drupal_add_http_header('Content-Type', 'application/json; utf-8');
  if ($data !== NULL) {
    print drupal_json_encode($data);
  }
  exit();
}
