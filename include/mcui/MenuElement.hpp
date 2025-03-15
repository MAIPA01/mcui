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

namespace mcui {
	class MenuElement {
	private:
		const std::string _name;

	public:
		MenuElement(const std::string& name) : _name(name) {}
		virtual ~MenuElement() = default;

		std::string getName() const {
			return _name;
		}

		virtual MenuExitState run() const = 0;
	};
}