#pragma once

#include <string>

#include "../Encryptor.h"

class AtbashCipher : public Encryptor {
	public:
		AtbashCipher(const std::string& PlainText);
		~AtbashCipher();

		void setPlainText(const std::string& newPlainText) override;

		std::string encrypt() override;
		std::string decrypt() override;
};
