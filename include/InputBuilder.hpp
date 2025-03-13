/*
 * mcui - MAIPA's Console User Interface
 *
 * Licensed under the BSD 3-Clause License with Attribution Requirement.
 * See the LICENSE file for details: https://github.com/MAIPA01/mcui/blob/main/LICENSE
 *
 * Copyright (c) 2025, Patryk Antosik (MAIPA01)
 */

#pragma once
#include "Input.hpp"
#include "InputSequence.hpp"

namespace mcui {
	class InputBuilder {
	private:

		static constexpr const char* _default_bad_value_message = "Invalid value was provided";
		static bool _default_value_checker(const std::string& value) {
			return value != "";
		}

		template<class F, class N, class... Ns, std::enable_if_t<mstd::are_arithmetic_v<N, Ns...>, bool> = true,
		std::enable_if_t<mstd::is_same_function_v<F, _input_checker_type>, bool> = true>
		static constexpr std::vector<InputElementSPtr> _makeSequenceInputs(const std::string& name, 
			const std::string& bad_value_message, const F& checker, bool is_optional,
			const N& size, const Ns&... sizes) {
			
			using UN = std::make_unsigned_t<N>;
			const UN& usize = static_cast<UN>(size);

			std::vector<InputElementSPtr> inputs = {};

			for (UN i = 0; i != size; ++i) {
				const std::string& inputName = name + "[" + std::to_string(i) + "]";
				if constexpr (sizeof...(Ns) == 0) {
					inputs.push_back(makeInput(inputName + ": ", bad_value_message, checker, is_optional));
				}
				else {
					const std::vector<InputElementSPtr> temp = 
						_makeSequenceInputs(inputName, bad_value_message, checker, is_optional, sizes...);
					inputs.reserve(inputs.size() + temp.size());
					inputs.insert(inputs.end(), temp.begin(), temp.end());
				}
			}

			return inputs;
		}

		InputBuilder() = default;
	public:
		virtual ~InputBuilder() = default;

		static InputSPtr makeInput(const std::string& message, bool is_optional = false) {
			return Input::create(message, _default_bad_value_message, is_optional,
				&_default_value_checker);
		}
		static InputSPtr makeInput(const std::string& message, const std::string& bad_value_message,
			bool is_optional = false) {
			return Input::create(message, bad_value_message, is_optional,
				&_default_value_checker);
		}
		template<class F, std::enable_if_t<mstd::is_same_function_v<F, _input_checker_type>, bool> = true>
		static InputSPtr makeInput(const std::string& message, const F& checker, bool is_optional = false) {
			return Input::create(message, _default_bad_value_message, is_optional, checker);
		}
		template<class F, std::enable_if_t<mstd::is_same_function_v<F, _input_checker_type>, bool> = true>
		static InputSPtr makeInput(const std::string& message, const std::string& bad_value_message,
			const F& checker, bool is_optional = false) {
			return Input::create(message, bad_value_message, is_optional, checker);
		}

		static InputSequenceSPtr makeSequenceInput(const std::vector<InputElementSPtr>& inputs) {
			return InputSequence::create("", inputs);
		}
		static InputSequenceSPtr makeSequenceInput(const std::string& message,
			const std::vector<InputElementSPtr>& inputs) {
			return InputSequence::create(message, inputs);
		}
		template<class... Elems, std::enable_if_t<_are_input_elements_v<Elems...>, bool> = true>
		static InputSequenceSPtr makeSequenceInput(const std::shared_ptr<Elems>&... inputs) {
			return makeSequenceInput({ inputs... });
		}
		template<class... Elems, std::enable_if_t<_are_input_elements_v<Elems...>, bool> = true>
		static InputSequenceSPtr makeSequenceInput(const std::string& message, 
			const std::shared_ptr<Elems>&... inputs) {
			return makeSequenceInput(message, { inputs... });
		}

		template<class... Ns, std::enable_if_t<mstd::are_arithmetic_v<Ns...>, bool> = true>
		static InputSequenceSPtr makeSequenceInput(const std::string& message, const std::string& item_name,
			bool is_optional, const Ns&... sizes) {
			return makeSequenceInput(message, _makeSequenceInputs(item_name, _default_bad_value_message,
				&_default_value_checker, is_optional, sizes...));
		}
		template<class... Ns, std::enable_if_t<mstd::are_arithmetic_v<Ns...>, bool> = true>
		static InputSequenceSPtr makeSequenceInput(const std::string& message, const std::string& item_name,
			const std::string& bad_value_message, bool is_optional, const Ns&... sizes) {
			return makeSequenceInput(message, _makeSequenceInputs(item_name, bad_value_message,
				&_default_value_checker, is_optional, sizes...));
		}
		template<class F, class... Ns, std::enable_if_t<mstd::are_arithmetic_v<Ns...>, bool> = true,
			std::enable_if_t<mstd::is_same_function_v<F, _input_checker_type>, bool> = true>
		static InputSequenceSPtr makeSequenceInput(const std::string& message, const std::string& item_name,
			const F& checker, bool is_optional, const Ns&... sizes) {
			return makeSequenceInput(message, _makeSequenceInputs(item_name, _default_bad_value_message,
				checker, is_optional, sizes...));
		}
		template<class F, class... Ns, std::enable_if_t<mstd::are_arithmetic_v<Ns...>, bool> = true,
			std::enable_if_t<mstd::is_same_function_v<F, _input_checker_type>, bool> = true>
		static InputSequenceSPtr makeSequenceInput(const std::string& message, const std::string& item_name,
			const std::string& bad_value_message, const F& checker, bool is_optional, const Ns&... sizes) {
			return makeSequenceInput(message, _makeSequenceInputs(item_name, bad_value_message,
				checker, is_optional, sizes...));
		}
	};
}