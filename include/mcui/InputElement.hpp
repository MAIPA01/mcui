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
	class InputElement {
	private:
		const std::string _message;

	public:
		InputElement(const std::string& message) : _message(message) {}
		virtual ~InputElement() = default;

		std::string getMessage() const {
			return _message;
		}

		virtual std::vector<std::string> run() const = 0;
	};
}