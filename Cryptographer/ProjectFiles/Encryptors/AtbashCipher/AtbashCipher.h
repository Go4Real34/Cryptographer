#pragma once

#include "../Encryptor.h"

class AtbashCipher : public Encryptor {
	public:
		AtbashCipher(const std::string& PlainText);
		~AtbashCipher();

		void setPlainText(const std::string& newPlainText);

		std::string encrypt() override;
		std::string decrypt() override;

	private:
		const int8_t ASCII_CODE_OF_UPPERCASE_A = 65;
		const int8_t ASCII_CODE_OF_UPPERCASE_Z = 90;
		const int8_t ASCII_CODE_OF_LOWERCASE_A = 97;
		const int8_t ASCII_CODE_OF_LOWERCASE_Z = 122;

		char encryptCharacter(const char& character) const;
		char decryptCharacter(const char& character) const;

		int8_t getCorrespondingIndexDifference(const char& character, const bool& isEncrypting) const;
};
