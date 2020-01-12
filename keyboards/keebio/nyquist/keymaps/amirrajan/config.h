/*
Copyright 2017 Danny Nguyen <danny@hexwire.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#define TAPPING_TOGGLE  1
#define TAPPING_TERM    170
#define PREVENT_STUCK_MODIFIERS
#define LOCKING_RESYNC_ENABLE
#define LOCKING_SUPPORT_ENABLE
#define IGNORE_MOD_TAP_INTERRUPT
#define MASTER_LEFT
#define DISABLE_SPACE_CADET_ROLLOVER
#undef  BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 1
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

#endif
