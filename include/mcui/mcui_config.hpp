/*
 * mcui - MAIPA's Console User Interface
 *
 * Licensed under the BSD 3-Clause License with Attribution Requirement.
 * See the LICENSE file for details: https://github.com/MAIPA01/mcui/blob/main/LICENSE
 *
 * Copyright (c) 2025, Patryk Antosik (MAIPA01)
 */

#pragma once
#pragma region VERSION
#define MCUI_VERSION_MAJOR 1
#define MCUI_VERSION_MINOR 0
#define MCUI_VERSION_PATCH 0

#define MCUI_VERSION_TO_STRING(major, minor, patch) #major #minor #patch
#define MCUI_VERSION_TO_INT(major, minor, patch) (major * 100 + minor * 10 + patch)

#define MCUI_VERSION_STRING MCUI_VERSION_TO_STRING(MCUI_VERSION_MAJOR, \
												MCUI_VERSION_MINOR, \
												MCUI_VERSION_PATCH)
#define MCUI_VERSION_INT MCUI_VERSION_TO_INT(MCUI_VERSION_MAJOR, \
											MCUI_VERSION_MINOR, \
											MCUI_VERSION_PATCH)
#define MCUI_VERSION MCUI_VERSION_STRING
#pragma endregion

#pragma region LAST_UPDATE
#define MCUI_LAST_UPDATE_DAY 13
#define MCUI_LAST_UPDATE_MONTH 3
#define MCUI_LAST_UPDATE_YEAR 2025

#define MCUI_LAST_UPDATE_DATE "13.03.2025"
#pragma endregion