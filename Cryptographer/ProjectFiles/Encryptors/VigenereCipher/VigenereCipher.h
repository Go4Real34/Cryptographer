#pragma once

#include "../Encryptor.h"

class VigenereCipher : public Encryptor {
	public:
		VigenereCipher(const std::string& PlainText, const std::string& Key);
		~VigenereCipher();

		void setPlainText(const std::string& newPlainText) override;
		void setKey(const std::string& newKey);

		std::string encrypt() override;
		std::string decrypt() override;

	private:
		std::string key = "";
		size_t keySize = 0;

		char encryptCharacter(const char& textCharacter, const char& keyCharacter);
		char decryptCharacter(const char& textCharacter, const char& keyCharacter);
};
