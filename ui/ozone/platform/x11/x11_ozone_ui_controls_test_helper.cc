// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/ozone/platform/x11/x11_ozone_ui_controls_test_helper.h"

namespace ui {

X11OzoneUIControlsTestHelper::X11OzoneUIControlsTestHelper() = default;
X11OzoneUIControlsTestHelper::~X11OzoneUIControlsTestHelper() = default;

bool X11OzoneUIControlsTestHelper::SupportsScreenCoordinates() const {
  return true;
}

unsigned X11OzoneUIControlsTestHelper::ButtonDownMask() const {
  return x11_ui_controls_test_helper_.ButtonDownMask();
}

void X11OzoneUIControlsTestHelper::SendKeyEvents(gfx::AcceleratedWidget widget,
                                                 ui::KeyboardCode key,
                                                 int key_event_types,
                                                 int accelerator_state,
                                                 base::OnceClosure closure) {
  x11_ui_controls_test_helper_.SendKeyEvents(
      widget, key, key_event_types, accelerator_state, std::move(closure));
}

void X11OzoneUIControlsTestHelper::SendMouseMotionNotifyEvent(
    gfx::AcceleratedWidget widget,
    const gfx::Point& mouse_loc,
    const gfx::Point& mouse_root_loc,
    base::OnceClosure closure) {
  x11_ui_controls_test_helper_.SendMouseMotionNotifyEvent(
      widget, mouse_loc, mouse_root_loc, std::move(closure));
}

void X11OzoneUIControlsTestHelper::SendMouseEvent(
    gfx::AcceleratedWidget widget,
    ui_controls::MouseButton type,
    int button_state,
    int accelerator_state,
    const gfx::Point& mouse_loc,
    const gfx::Point& mouse_root_loc,
    base::OnceClosure closure) {
  x11_ui_controls_test_helper_.SendMouseEvent(
      widget, type, button_state, accelerator_state, mouse_loc, mouse_root_loc,
      std::move(closure));
}

void X11OzoneUIControlsTestHelper::RunClosureAfterAllPendingUIEvents(
    base::OnceClosure closure) {
  x11_ui_controls_test_helper_.RunClosureAfterAllPendingUIEvents(
      std::move(closure));
}

bool X11OzoneUIControlsTestHelper::MustUseUiControlsForMoveCursorTo() {
  return false;
}

OzoneUIControlsTestHelper* CreateOzoneUIControlsTestHelperX11() {
  return new X11OzoneUIControlsTestHelper();
}

}  // namespace ui
