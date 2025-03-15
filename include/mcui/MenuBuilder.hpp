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
#include "MenuOption.hpp"
#include "Menu.hpp"

namespace mcui {
	class MenuBuilder {
	private:
		MenuBuilder() = default;

		static mstd::ordered_map<std::string, MenuElementSPtr>
			_makeSequenceElements(const std::vector<MenuElementSPtr>& elements) {
			mstd::ordered_map<std::string, MenuElementSPtr> sequence_elements;
			for (size_t i = 0; i != elements.size(); ++i) {
				sequence_elements.insert(sequence_elements.end(), 
					{ std::to_string(i + 1), elements[i] });
			}
			return sequence_elements;
		}
	public:
		virtual ~MenuBuilder() = default;

#pragma region MENU_ELEMENT
		static std::pair<std::string, MenuElementSPtr> makeMenuElement(const std::string option, 
			const MenuElementSPtr& element) {
			return { option, element };
		}

		template<class F, std::enable_if_t<_is_valid_option_function<F>, bool> = true>
		static std::pair<std::string, MenuElementSPtr> makeMenuElement(const std::string option,
			const std::string& name, const F& callback) {
			return makeMenuElement(option, makeOption(name, callback));
		}
#pragma endregion // MENU ELEMENT

#pragma region OPTION
		template<class F, std::enable_if_t<_is_valid_option_function<F>, bool> = true>
		static MenuOptionSPtr makeOption(const std::string& name, const F& callback) {
			return MenuOption::create(name, callback);
		}
#pragma endregion // OPTION

#pragma region MENU
		template<class _View>
		static MenuSPtr<_View> makeMenu(const std::string& name, bool clear_terminal,
			const mstd::ordered_map<std::string, MenuElementSPtr>& elements) {
			return Menu<_View>::create(name, clear_terminal, elements);
		}
		template<class _View>
		static MenuSPtr<_View> makeMenu(const std::string& name, bool clear_terminal,
			const std::vector<MenuElementSPtr>& elements) {
			return makeMenu<_View>(name, clear_terminal, _makeSequenceElements(elements));
		}

		template<class _View, class... Elems, std::enable_if_t<_are_menu_elements_v<Elems...>, bool> = true>
		static MenuSPtr<_View> makeMenu(const std::string& name, bool clear_terminal, 
			const std::pair<std::string, std::shared_ptr<Elems>>&... elements) {
			return makeMenu<_View>(name, clear_terminal, 
				mstd::ordered_map<std::string, MenuElementSPtr>{ elements... });
		}
		template<class _View, class... Elems, std::enable_if_t<_are_menu_elements_v<Elems...>, bool> = true>
		static MenuSPtr<_View> makeMenu(const std::string& name, bool clear_terminal,
			const std::shared_ptr<Elems>&... elements) {
			return makeMenu<_View>(name, clear_terminal, std::vector<MenuElementSPtr>{ elements... });
		}
#pragma endregion // MENU

#pragma region STANDARD_MENU
		static StandardMenuSPtr makeStandardMenu(const std::string& name, bool clear_terminal,
			const mstd::ordered_map<std::string, MenuElementSPtr>& elements) {
			return makeMenu<StandardMenuView>(name, clear_terminal, elements);
		}
		static StandardMenuSPtr makeStandardMenu(const std::string& name, bool clear_terminal,
			bool add_back, bool add_exit, const mstd::ordered_map<std::string, MenuElementSPtr>& elements) {
			mstd::ordered_map<std::string, MenuElementSPtr> elements_vec = elements;
			if (add_back) {
				elements_vec.insert(elements_vec.end(), { "back",
					makeOption("Back", []() -> MenuExitState { return MenuExitState::Back; })
					});
			}
			if (add_exit) {
				elements_vec.insert(elements_vec.end(), { "exit",
					makeOption("Exit", []() -> MenuExitState { return MenuExitState::Exit; })
					});
			}
			return makeMenu<StandardMenuView>(name, clear_terminal, elements_vec);
		}
		static StandardMenuSPtr makeStandardMenu(const std::string& name, bool clear_terminal,
			const std::vector<MenuElementSPtr>& elements) {
			return makeStandardMenu(name, clear_terminal, _makeSequenceElements(elements));
		}
		static StandardMenuSPtr makeStandardMenu(const std::string& name, bool clear_terminal,
			bool add_back, bool add_exit, const std::vector<MenuElementSPtr>& elements) {
			return makeStandardMenu(name, clear_terminal, add_back, add_exit, _makeSequenceElements(elements));
		}

		template<class... Elems, std::enable_if_t<_are_menu_elements_v<Elems...>, bool> = true>
		static StandardMenuSPtr makeStandardMenu(const std::string& name, bool clear_terminal,
			const std::pair<std::string, std::shared_ptr<Elems>>&... elements) {
			return makeStandardMenu(name, clear_terminal, 
				mstd::ordered_map<std::string, MenuElementSPtr>{ elements... });
		}
		template<class... Elems, std::enable_if_t<_are_menu_elements_v<Elems...>, bool> = true>
		static StandardMenuSPtr makeStandardMenu(const std::string& name, bool clear_terminal,
			bool add_back, bool add_exit, const std::pair<std::string, std::shared_ptr<Elems>>&... elements) {
			return makeStandardMenu(name, clear_terminal, add_back, add_exit, 
				mstd::ordered_map<std::string, MenuElementSPtr>{ elements... });
		}
		template<class... Elems, std::enable_if_t<_are_menu_elements_v<Elems...>, bool> = true>
		static StandardMenuSPtr makeStandardMenu(const std::string& name, bool clear_terminal,
			const std::shared_ptr<Elems>&... elements) {
			return makeStandardMenu(name, clear_terminal, std::vector<MenuElementSPtr>{ elements... });
		}
		template<class... Elems, std::enable_if_t<_are_menu_elements_v<Elems...>, bool> = true>
		static StandardMenuSPtr makeStandardMenu(const std::string& name, bool clear_terminal,
			bool add_back, bool add_exit, const std::shared_ptr<Elems>&... elements) {
			return makeStandardMenu(name, clear_terminal, add_back, add_exit, 
				std::vector<MenuElementSPtr>{ elements... });
		}
#pragma endregion // STANDARD_MENU

#pragma region YES_NO_MENU
		template<class YF, class NF, 
			std::enable_if_t<(_is_valid_option_function<YF> && _is_valid_option_function<NF>), bool> = true>
		static YesNoMenuSPtr makeYesNoMenu(const std::string& message, const YF& yes_callback, 
			const NF& no_callback) {
			const _option_callback_type& yes_lambda = 
				[yes_callback]() -> MenuExitState { yes_callback(); return MenuExitState::Back; };
			const _option_callback_type& no_lambda = 
				[no_callback]() -> MenuExitState { no_callback(); return MenuExitState::Back; };

			return makeMenu<YesNoMenuView>(message, false, {
				{ "Y", makeOption("", yes_lambda)},
				{ "y", makeOption("", yes_lambda)},
				{ "N", makeOption("", no_lambda)},
				{ "n", makeOption("", no_lambda)}
			});
		}
#pragma endregion // YES_NO_MENU
	};
}