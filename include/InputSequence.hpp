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
	class InputSequence : public InputElement {
	private:
		const std::vector<InputElementSPtr> _inputs;

	public:
		InputSequence(const std::string& message, const std::vector<InputElementSPtr>& inputs) 
			: InputElement(message), _inputs(inputs) {}
		virtual ~InputSequence() = default;

		static InputSequenceSPtr create(const std::string& message, const std::vector<InputElementSPtr>& inputs) {
			return std::make_shared<InputSequence>(message, inputs);
		}

		std::vector<InputElementSPtr> getInputs() const {
			return _inputs;
		}

		std::vector<std::string> run() const override {
			const std::string& message = getMessage();
			if (message != "") std::cout << message << std::endl;

			std::vector<std::string> values = {};

			for (const InputElementSPtr& input : _inputs) {
				const std::vector<std::string>& temp = input->run();
				values.reserve(values.size() + temp.size());
				values.insert(values.end(), temp.begin(), temp.end());
			}

			return values;
		}
	};
}