#pragma once

#include <string>

#include "../Encryptor.h"

class CaesarCipher : public Encryptor {
	public:
		CaesarCipher(const std::string& PlainText, uint8_t ShiftAmount);
		~CaesarCipher();

		void setPlainText(const std::string& newPlainText) override;
		void setShiftAmount(uint8_t newShiftAmount);

		std::string encrypt() override;
		std::string decrypt() override;

	private:
		uint8_t shiftAmount = 0;
};
