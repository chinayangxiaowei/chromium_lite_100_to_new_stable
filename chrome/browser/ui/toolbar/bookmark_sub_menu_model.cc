// Copyright 2011 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/toolbar/bookmark_sub_menu_model.h"

#include "build/build_config.h"
#include "build/chromeos_buildflags.h"
#include "chrome/app/chrome_command_ids.h"
#include "chrome/grit/generated_resources.h"

DEFINE_CLASS_ELEMENT_IDENTIFIER_VALUE(BookmarkSubMenuModel,
                                      kShowBookmarkBarMenuItem);

// For views and cocoa, we have complex delegate systems to handle
// injecting the bookmarks to the bookmark submenu. This is done to support
// advanced interactions with the menu contents, like right click context menus.

BookmarkSubMenuModel::BookmarkSubMenuModel(
    ui::SimpleMenuModel::Delegate* delegate, Browser* browser)
    : SimpleMenuModel(delegate) {
  Build(browser);
}

BookmarkSubMenuModel::~BookmarkSubMenuModel() {}

void BookmarkSubMenuModel::Build(Browser* browser) {
  bool is_submenu_visible =
      delegate()->IsCommandIdVisible(IDC_BOOKMARK_THIS_TAB) ||
      delegate()->IsCommandIdVisible(IDC_BOOKMARK_ALL_TABS);
#if BUILDFLAG(IS_WIN)
  is_submenu_visible |=
      delegate()->IsCommandIdVisible(IDC_PIN_TO_START_SCREEN);
#endif

  if (is_submenu_visible) {
    AddItemWithStringId(IDC_BOOKMARK_THIS_TAB, IDS_BOOKMARK_THIS_TAB);
    AddItemWithStringId(IDC_BOOKMARK_ALL_TABS, IDS_BOOKMARK_ALL_TABS);

#if BUILDFLAG(IS_WIN)
    AddItemWithStringId(IDC_PIN_TO_START_SCREEN, IDS_PIN_TO_START_SCREEN);
#endif
    AddSeparator(ui::NORMAL_SEPARATOR);
  }
  AddCheckItemWithStringId(IDC_SHOW_BOOKMARK_BAR, IDS_SHOW_BOOKMARK_BAR);
  SetElementIdentifierAt(GetIndexOfCommandId(IDC_SHOW_BOOKMARK_BAR).value(),
                         kShowBookmarkBarMenuItem);
  AddItemWithStringId(IDC_SHOW_BOOKMARK_MANAGER, IDS_BOOKMARK_MANAGER);
#if !BUILDFLAG(IS_CHROMEOS_ASH)
  AddItemWithStringId(IDC_IMPORT_SETTINGS, IDS_IMPORT_SETTINGS_MENU_LABEL);
#endif
}
