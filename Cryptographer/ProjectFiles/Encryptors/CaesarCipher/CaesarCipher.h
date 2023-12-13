#pragma once

#include "../Encryptor.h"

class CaesarCipher : public Encryptor {
	public:
		CaesarCipher(const std::string& PlainText, const long long& ShiftAmount);
		~CaesarCipher();

		void setPlainText(const std::string& newPlainText) override;
		void setShiftAmount(int8_t newShiftAmount);

		std::string encrypt() override;
		std::string decrypt() override;

	private:
		int8_t shiftAmount = 0;
		const int8_t englishAlphabetSize = 26;

		const int8_t ASCII_CODE_OF_UPPERCASE_A = 65;
		const int8_t ASCII_CODE_OF_UPPERCASE_Z = 90;
		const int8_t ASCII_CODE_OF_LOWERCASE_A = 97;
		const int8_t ASCII_CODE_OF_LOWERCASE_Z = 122;

		char encryptCharacter(const char& character) const;
		char decryptCharacter(const char& character) const;

		int8_t modulus(const long long& dividend, const int8_t& divisor) const;
};
