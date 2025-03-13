/*
 * mcui - MAIPA's Console User Interface
 *
 * Licensed under the BSD 3-Clause License with Attribution Requirement.
 * See the LICENSE file for details: https://github.com/MAIPA01/mcui/blob/main/LICENSE
 *
 * Copyright (c) 2025, Patryk Antosik (MAIPA01)
 */

#pragma once
#include "MenuElement.hpp"
#include "MenuViews.hpp"

// TODO: generate menu view on construction
// TODO: add default
namespace mcui {
	template<class _View>
	class Menu : public MenuElement {
	private:
		const mstd::ordered_map<std::string, MenuElementSPtr> _elements;
		const bool _clear_terminal;
		
	public:
		using view_type = _View;

		Menu(const std::string& name, bool clear_terminal, 
			const mstd::ordered_map<std::string, MenuElementSPtr>& elements)
			: MenuElement(name), _clear_terminal(clear_terminal), _elements(elements) {}

		virtual ~Menu() = default;

		static MenuSPtr<_View> create(const std::string& name, bool clear_terminal,
			const mstd::ordered_map<std::string, MenuElementSPtr>& elements) {
			return std::make_shared<Menu<_View>>(name, clear_terminal, elements);
		}

		mstd::ordered_map<std::string, MenuElementSPtr> getElements() const { return _elements; }

		MenuExitState run() const override {
			std::string line = "";

			// clear cmd
			if (_clear_terminal) mstd::clear_terminal();

			while (true) {
				_View::printView(getName(), _elements);

				// wait for input
				std::getline(std::cin, line);

				// trim
				line = mstd::trim(line);

				// clear cmd
				if (_clear_terminal) mstd::clear_terminal();

				// execute choosed element else throw error message
				if (_elements.contains(line)) {
					switch (_elements[line]->run()) {
					case MenuExitState::Back:
						return MenuExitState::None;
					case MenuExitState::Exit:
						return MenuExitState::Exit;
					// if not exit or back then do nothing
					}
				}
				else {
					std::cout << "Choosed option not recognized '" << line << "'" << std::endl << std::endl;
				}
			}
		}
	};
}