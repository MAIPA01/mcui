/*
 * mcui - MAIPA's Console User Interface
 *
 * Licensed under the BSD 3-Clause License with Attribution Requirement.
 * See the LICENSE file for details: https://github.com/MAIPA01/mcui/blob/main/LICENSE
 *
 * Copyright (c) 2025, Patryk Antosik (MAIPA01)
 */

#pragma once
#include "InputElement.hpp"

namespace mcui {
	class Input : public InputElement {
	private:
		const std::string _bad_value_message;
		const bool _is_optional;
		const _input_checker_type _checker;

	public:
		template<class F, std::enable_if_t<mstd::is_same_function_v<F, _input_checker_type>, bool> = true>
		Input(const std::string& message, const std::string& bad_value_message, bool is_optional, const F& checker)
			: InputElement(message), _bad_value_message(bad_value_message), _is_optional(is_optional), 
			_checker(checker) {}
		virtual ~Input() = default;

		template<class F, std::enable_if_t<mstd::is_same_function_v<F, _input_checker_type>, bool> = true>
		static InputSPtr create(const std::string& message, const std::string& bad_value_message,
			bool is_optional, const F& checker) {
			return std::make_shared<Input>(message, bad_value_message, is_optional, checker);
		}

		std::string getBadValueMessage() const {
			return _bad_value_message;
		}
		bool isOptional() const {
			return _is_optional;
		}
		_input_checker_type getChecker() const {
			return _checker;
		}

		std::vector<std::string> run() const override {
			while (true) {
				std::cout << this->getMessage();

				std::string value;
				std::getline(std::cin, value);

				if (_is_optional && value == "") {
					return std::vector<std::string>{ value };
				}

				if (!_checker(value)) {
					std::cout << _bad_value_message << std::endl;
					continue;
				}

				return std::vector<std::string>{ value };
			}
		}
	};
}