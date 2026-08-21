// Copyright 2024 Santosh Kumar (@santosh)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Luna reads mods, caps lock and typing activity to pick a pose. None of that
 * exists on the slave half unless it is synced across the split link. */
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_ACTIVITY_ENABLE
