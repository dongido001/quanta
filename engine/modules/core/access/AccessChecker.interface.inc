<?php
/**
 * Interface AccessChecker
 *
 * Simple interface for static access methods.
 */
interface AccessChecker {
  /**
   * Check access to a certain action.
   *
   * @param Environment $env
   *   The Environment.
   * @param string $action
   *   The action to check.
   * @param array $vars
   *    Misc variables.
   *
   * @return bool
   *   True if user has access to the action.
   */
  static function check($env, $action, $vars = array());
}