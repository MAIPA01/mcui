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
#define MCUI_VERSION_PATCH 1

#define _MCUI_STRINGIFY_HELPER(x) #x

#define _MCUI_VERSION_TO_STRING(major, minor, patch) _MCUI_STRINGIFY_HELPER(major)"."\
														_MCUI_STRINGIFY_HELPER(minor)"."\
														_MCUI_STRINGIFY_HELPER(patch)

#define _MCUI_VERSION_TO_INT(major, minor, patch) (major * 100 + minor * 10 + patch)

#define MCUI_VERSION_STRING _MCUI_VERSION_TO_STRING(MCUI_VERSION_MAJOR, \
												MCUI_VERSION_MINOR, \
												MCUI_VERSION_PATCH)
#define MCUI_VERSION_INT _MCUI_VERSION_TO_INT(MCUI_VERSION_MAJOR, \
											MCUI_VERSION_MINOR, \
											MCUI_VERSION_PATCH)
#define MCUI_VERSION MCUI_VERSION_STRING
#pragma endregion

#pragma region LAST_UPDATE
#define MCUI_LAST_UPDATE_DAY 4
#define MCUI_LAST_UPDATE_MONTH 10
#define MCUI_LAST_UPDATE_YEAR 2025

#define _MCUI_LAST_UPDATE_DATE_HELPER(day, month, year) _MCUI_STRINGIFY_HELPER(day)"."\
															_MCUI_STRINGIFY_HELPER(month)"."\
															_MCUI_STRINGIFY_HELPER(year)

#define MCUI_LAST_UPDATE_DATE _MCUI_LAST_UPDATE_DATE_HELPER(MCUI_LAST_UPDATE_DAY, \
																	MCUI_LAST_UPDATE_MONTH, \
																	MCUI_LAST_UPDATE_YEAR)
#pragma endregion