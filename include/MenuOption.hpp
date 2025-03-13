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

namespace mcui {
	class MenuOption : public MenuElement {
	private:
		const _option_callback_type _callback;

		template<class F, std::enable_if_t<_is_valid_option_function<F>, bool> = true>
		static constexpr _option_callback_type _make_lambda(const F& func) {
			if constexpr (mstd::is_same_function_v<F, _option_callback_type>) {
				return func;
			}
			else {
				return [func]() -> MenuExitState { func(); return MenuExitState::None; };
			}
		}

	public:
		template<class F, std::enable_if_t<_is_valid_option_function<F>, bool> = true>
		MenuOption(const std::string& name, const F& callback)
			: MenuElement(name), _callback(_make_lambda(callback)) {}

		virtual ~MenuOption() = default;

		template<class F, std::enable_if_t<_is_valid_option_function<F>, bool> = true>
		static OptionSPtr create(const std::string& name, const F& callback) {
			return std::make_shared<Option>(name, callback);
		}

		_option_callback_type getCallback() const {
			return _callback;
		}

		MenuExitState run() const override {
			return _callback();
		}
	};
}