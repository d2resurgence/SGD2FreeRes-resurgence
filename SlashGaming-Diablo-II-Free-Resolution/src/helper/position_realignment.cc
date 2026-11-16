/**
 * SlashGaming Diablo II Free Resolution
 * Copyright (C) 2019-2024  Mir Drualga
 *
 * This file is part of SlashGaming Diablo II Free Resolution.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Additional permissions under GNU Affero General Public License version 3
 *  section 7
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with Diablo II (or a modified version of that game and its
 *  libraries), containing parts covered by the terms of Blizzard End User
 *  License Agreement, the licensors of this Program grant you additional
 *  permission to convey the resulting work. This additional permission is
 *  also extended to any combination of expansions, mods, and remasters of
 *  the game.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any Graphics Device Interface (GDI), DirectDraw, Direct3D,
 *  Glide, OpenGL, or Rave wrapper (or modified versions of those
 *  libraries), containing parts not covered by a compatible license, the
 *  licensors of this Program grant you additional permission to convey the
 *  resulting work.
 *
 *  If you modify this Program, or any covered work, by linking or combining
 *  it with any library (or a modified version of that library) that links
 *  to Diablo II (or a modified version of that game and its libraries),
 *  containing parts not covered by a compatible license, the licensors of
 *  this Program grant you additional permission to convey the resulting
 *  work.
 */

#include "position_realignment.hpp"

#include "../config.hpp"
#include "game_resolution.hpp"

namespace sgd2fr {
namespace {

// 800x600's own ScreenShiftX: each side panel 80 pixels in from its
// edge, with the original 800 border frame filling those pixels.
constexpr int kScreenShiftXAtEdges = (800 - 640) / 2;

int GetCenteredScreenShiftX(int display_width) {
  return (display_width / 2) - (640 / 2);
}

} // namespace

int GetScreenShiftX(int display_width) {
  int centered_screen_shift_x = GetCenteredScreenShiftX(display_width);

  if (!config::IsSidePanelsAtScreenEdges()
      || centered_screen_shift_x <= kScreenShiftXAtEdges) {
    return centered_screen_shift_x;
  }

  return kScreenShiftXAtEdges;
}

bool AreSidePanelsAtScreenEdges(int display_width) {
  return GetScreenShiftX(display_width)
      != GetCenteredScreenShiftX(display_width);
}

void RealignPositionToSidePanel(
    ::d2::PositionalRectangle_Wrapper out_position_wrapper) {
  Resolution current_resolution =
      GetIngameResolutionFromId(::d2::d2gfx::GetResolutionMode());

  if (!AreSidePanelsAtScreenEdges(current_resolution.width)) {
    RealignPositionFromCenter(out_position_wrapper);
    return;
  }

  Resolution source_resolution = GetSourceInventoryArrangeResolution();

  int current_screen_shift_x = GetScreenShiftX(current_resolution.width);
  int source_screen_shift_x =
      GetCenteredScreenShiftX(source_resolution.width);

  // A left panel's pieces sit at ScreenShiftX + k, a right panel's at
  // width - ScreenShiftX - k, in the source arrangement and on screen.
  int offset_x;
  if (out_position_wrapper.GetLeft() < (source_resolution.width / 2)) {
    offset_x = current_screen_shift_x - source_screen_shift_x;
  } else {
    offset_x = (current_resolution.width - current_screen_shift_x)
        - (source_resolution.width - source_screen_shift_x);
  }

  int rectangle_width =
      out_position_wrapper.GetRight() - out_position_wrapper.GetLeft();

  out_position_wrapper.SetLeft(out_position_wrapper.GetLeft() + offset_x);
  out_position_wrapper.SetRight(
      out_position_wrapper.GetLeft() + rectangle_width);

  // Set top and bottom values, as RealignPositionFromCenter does.
  int dist_from_rect_top_to_display_center =
      out_position_wrapper.GetTop() - (source_resolution.height / 2);

  int rectangle_height =
      out_position_wrapper.GetBottom() - out_position_wrapper.GetTop();

  out_position_wrapper.SetTop(
      (current_resolution.height / 2) + dist_from_rect_top_to_display_center);

  out_position_wrapper.SetBottom(
      out_position_wrapper.GetTop() + rectangle_height);
}

void RealignPositionFromCenter(
    ::d2::PositionalRectangle_Wrapper out_position_wrapper) {
  Resolution current_resolution =
      GetIngameResolutionFromId(::d2::d2gfx::GetResolutionMode());

  Resolution source_resolution = GetSourceInventoryArrangeResolution();

  // Set left and right values.
  int dist_from_rect_left_to_display_center =
      out_position_wrapper.GetLeft() - (source_resolution.width / 2);

  int rectangle_width =
      out_position_wrapper.GetRight() - out_position_wrapper.GetLeft();

  out_position_wrapper.SetLeft(
      (current_resolution.width / 2) + dist_from_rect_left_to_display_center);

  out_position_wrapper.SetRight(
      out_position_wrapper.GetLeft() + rectangle_width);

  // Set top and bottom values.
  int dist_from_rect_top_to_display_center =
      out_position_wrapper.GetTop() - (source_resolution.height / 2);

  int rectangle_height =
      out_position_wrapper.GetBottom() - out_position_wrapper.GetTop();

  out_position_wrapper.SetTop(
      (current_resolution.height / 2) + dist_from_rect_top_to_display_center);

  out_position_wrapper.SetBottom(
      out_position_wrapper.GetTop() + rectangle_height);
}

void RealignPositionFromBottomCenter(
    d2::PositionalRectangle_Wrapper out_position_wrapper) {
  Resolution current_resolution =
      GetIngameResolutionFromId(d2::d2gfx::GetResolutionMode());

  Resolution source_resolution = GetSourceInventoryArrangeResolution();

  // Set left and right values.
  int dist_from_rect_left_to_display_center =
      out_position_wrapper.GetLeft() - (source_resolution.width / 2);

  int rectangle_width =
      out_position_wrapper.GetRight() - out_position_wrapper.GetLeft();

  out_position_wrapper.SetLeft(
      (current_resolution.width / 2) + dist_from_rect_left_to_display_center);

  out_position_wrapper.SetRight(
      out_position_wrapper.GetLeft() + rectangle_width);

  // Set top and bottom values.
  int dist_from_rect_top_to_display_bottom = 
      source_resolution.height - out_position_wrapper.GetTop();

  int rectangle_height =
      out_position_wrapper.GetBottom() - out_position_wrapper.GetTop();

  out_position_wrapper.SetTop(
      current_resolution.height - dist_from_rect_top_to_display_bottom);

  out_position_wrapper.SetBottom(
      out_position_wrapper.GetTop() + rectangle_height);
}

} // namespace sgd2fr

