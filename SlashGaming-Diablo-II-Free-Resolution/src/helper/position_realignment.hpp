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

#ifndef SGD2FR_HELPER_POSITION_REALIGNMENT_HPP_
#define SGD2FR_HELPER_POSITION_REALIGNMENT_HPP_

#include <sgd2mapi.hpp>

namespace sgd2fr {

void RealignPositionFromCenter(
    ::d2::PositionalRectangle_Wrapper out_position_wrapper
);

void RealignPositionFromBottomCenter(
    ::d2::PositionalRectangle_Wrapper out_position_wrapper
);

/**
 * D2Client draws a left side panel at ScreenShiftX + k and a right side
 * panel at width - ScreenShiftX - k, so this one value sets how far in
 * from the screen's edges the side panels sit.
 */
int GetScreenShiftX(int display_width);

/**
 * True when the side panels are configured to sit at the screen's
 * edges and the display is wide enough for that to differ from
 * centering them.
 */
bool AreSidePanelsAtScreenEdges(int display_width);

/**
 * Realigns a rectangle of the source inventory arrangement with the side
 * panel it belongs to: one whose left edge is left of the source's
 * center moves with the left panel, any other with the right panel.
 * Centered panels give the same result as RealignPositionFromCenter.
 */
void RealignPositionToSidePanel(
    ::d2::PositionalRectangle_Wrapper out_position_wrapper
);

} // namespace sgd2fr

#endif // SGD2FR_HELPER_POSITION_REALIGNMENT_HPP_
