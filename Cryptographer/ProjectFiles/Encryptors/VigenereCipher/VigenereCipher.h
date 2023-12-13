#pragma once

#include "../Encryptor.h"

class VigenereCipher : public Encryptor {
	public:
		VigenereCipher(const std::string& PlainText, std::string& Key);
		~VigenereCipher();

		void setPlainText(const std::string& newPlainText);
		void setKey(std::string& newKey);

		std::string encrypt() override;
		std::string decrypt() override;

	private:
		std::string key = "";
		size_t keySize = 0;
		
		std::string equalizedKey = "";
		size_t equalizedKeySize = 0;

		const int8_t englishAlphabetSize = 26;

		const int8_t ASCII_CODE_OF_UPPERCASE_A = 65;
		const int8_t ASCII_CODE_OF_UPPERCASE_Z = 90;
		const int8_t ASCII_CODE_OF_LOWERCASE_A = 97;
		const int8_t ASCII_CODE_OF_LOWERCASE_Z = 122;

		char encryptCharacter(const char& textCharacter, const char& keyCharacter) const;
		char decryptCharacter(const char& textCharacter, const char& keyCharacter) const;

		std::string createEqualSizedKey() const;
		int8_t getAlphabetIndex(const char& character, const bool& isLowerCase) const;
		char getAlphabetCharacter(const int8_t& alphabetIndex, const bool& isLowerCase) const;

		int8_t modulus(const int8_t& dividend, const int8_t& divisor) const;
};
