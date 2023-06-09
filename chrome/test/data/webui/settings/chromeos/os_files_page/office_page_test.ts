// Copyright 2023 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

import 'chrome://os-settings/chromeos/lazy_load.js';

import {SettingsOfficePageElement} from 'chrome://os-settings/chromeos/lazy_load.js';
import {CrSettingsPrefs, SettingsPrefsElement, SettingsToggleButtonElement} from 'chrome://os-settings/chromeos/os_settings.js';
import {assert} from 'chrome://resources/js/assert_ts.js';
import {flush} from 'chrome://resources/polymer/v3_0/polymer/polymer_bundled.min.js';
import {assertFalse, assertTrue} from 'chrome://webui-test/chai_assert.js';


suite('<settings-office-page>', function() {
  let page: SettingsOfficePageElement;
  let prefElement: SettingsPrefsElement;

  setup(async function() {
    prefElement = document.createElement('settings-prefs');
    document.body.appendChild(prefElement);

    await CrSettingsPrefs.initialized;
    page = document.createElement('settings-office-page');
    page.prefs = prefElement.prefs;
    document.body.appendChild(page);
    flush();
  });

  teardown(function() {
    page.remove();
    prefElement.remove();
  });

  test('Checked when pref is true', function() {
    page.setPrefValue('filebrowser.office.always_move', true);
    flush();

    const alwaysMove =
        page.shadowRoot!.querySelector<SettingsToggleButtonElement>(
            '#alwaysMove');
    assert(alwaysMove);
    assertTrue(alwaysMove.checked);
  });

  test('Unchecked when pref is false', function() {
    page.setPrefValue('filebrowser.office.always_move', false);
    flush();

    const alwaysMove =
        page.shadowRoot!.querySelector<SettingsToggleButtonElement>(
            '#alwaysMove');
    assert(alwaysMove);
    assertFalse(alwaysMove.checked);
  });

  test('Sets pref to true when clicked from false', function() {
    page.setPrefValue('filebrowser.office.always_move', false);
    flush();

    const alwaysMove =
        page.shadowRoot!.querySelector<SettingsToggleButtonElement>(
            '#alwaysMove');
    assert(alwaysMove);
    assertFalse(alwaysMove.checked);

    alwaysMove.click();
    assertTrue(alwaysMove.checked);
    assertTrue(page.getPref('filebrowser.office.always_move').value);
  });

  test('Sets pref to false when clicked from true', function() {
    page.setPrefValue('filebrowser.office.always_move', true);
    flush();

    const alwaysMove =
        page.shadowRoot!.querySelector<SettingsToggleButtonElement>(
            '#alwaysMove');
    assert(alwaysMove);
    assertTrue(alwaysMove.checked);

    alwaysMove.click();
    assertFalse(alwaysMove.checked);
    assertFalse(page.getPref('filebrowser.office.always_move').value);
  });
});
