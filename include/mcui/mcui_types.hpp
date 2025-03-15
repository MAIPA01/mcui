/*
 * mcui - MAIPA's Console User Interface
 *
 * Licensed under the BSD 3-Clause License with Attribution Requirement.
 * See the LICENSE file for details: https://github.com/MAIPA01/mcui/blob/main/LICENSE
 *
 * Copyright (c) 2025, Patryk Antosik (MAIPA01)
 */

#pragma once
#include "mcui_libs.hpp"

namespace mcui {
#pragma region MENU
	struct StandardMenuView;
	struct YesNoMenuView;

	class MenuElement;
	class MenuOption;
	template<class _View>
	class Menu;

	using StandardMenu = Menu<StandardMenuView>;
	using YesNoMenu = Menu<YesNoMenuView>;

	enum class MenuExitState {
		None = 0,
		Back = 1,
		Exit = 2
	};

	using MenuElementSPtr = std::shared_ptr<MenuElement>;
	using MenuOptionSPtr = std::shared_ptr<MenuOption>;
	template<class _View>
	using MenuSPtr = std::shared_ptr<Menu<_View>>;

	using StandardMenuSPtr = MenuSPtr<StandardMenuView>;
	using YesNoMenuSPtr = MenuSPtr<YesNoMenuView>;

	template<class... Elems>
	constexpr bool _are_menu_elements_v = (std::is_base_of_v<MenuElement, Elems> && ...);

	using _option_callback_type = std::function<MenuExitState(void)>;
	using _plain_option_callback_type = std::function<void(void)>;

	template<class F>
	static constexpr bool _is_valid_option_function = mstd::is_same_function_v<F, _option_callback_type> ||
		mstd::is_same_function_v<F, _plain_option_callback_type>;
#pragma endregion // MENU

#pragma region INPUT
	class InputElement;
	class Input;
	class InputSequence;

	class InputBuilder;

	using InputElementSPtr = std::shared_ptr<InputElement>;
	using InputSPtr = std::shared_ptr<Input>;
	using InputSequenceSPtr = std::shared_ptr<InputSequence>;

	using _input_checker_type = std::function<bool(const std::string&)>;

	template<class... Elems>
	constexpr bool _are_input_elements_v = (std::is_base_of_v<InputElement, Elems> && ...);
#pragma endregion // INPUT
}