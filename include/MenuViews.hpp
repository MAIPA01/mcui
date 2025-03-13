/*
 * mcui - MAIPA's Console User Interface
 *
 * Licensed under the BSD 3-Clause License with Attribution Requirement.
 * See the LICENSE file for details: https://github.com/MAIPA01/mcui/blob/main/LICENSE
 *
 * Copyright (c) 2025, Patryk Antosik (MAIPA01)
 */

#pragma once
#include "mcui_types.hpp"
#include "MenuElement.hpp"

namespace mcui {
	/*struct ViewSample {
		static void printView(const std::string& menu_name, 
			const mstd::ordered_map<std::string, MenuElementSPtr>& elements);
	};*/

	struct StandardMenuView {
		static void printView(const std::string& menu_name,
			const mstd::ordered_map<std::string, MenuElementSPtr>& elements) {
			// print menu name
			std::cout << menu_name << std::endl;

			// get max size
			size_t max_size = std::max_element(elements.begin(), elements.end(),
				[](const std::pair<std::string, MenuElementSPtr>& elem1, 
					const std::pair<std::string, MenuElementSPtr>& elem2) -> bool {
					return elem1.first.size() < elem2.first.size();
				})->first.size();

			// list all elements + back + exit
			for (const std::pair<std::string, MenuElementSPtr>& elem : elements) {
				std::cout << std::string(2, ' ') << elem.first << "." <<
					std::string(2 + (max_size - elem.first.size()), ' ') << elem.second->getName() << std::endl;
			}

			// for input
			std::cout << "> ";
		}
	};

	struct YesNoMenuView {
		static void printView(const std::string& menu_name,
			const mstd::ordered_map<std::string, MenuElementSPtr>& elements) {
			// print message
			std::cout << message << " (Y/n): ";
		}
	};
}