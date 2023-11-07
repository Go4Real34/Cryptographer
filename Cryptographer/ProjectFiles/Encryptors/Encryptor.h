#pragma once

#include <string>

class Encryptor {
	public:
		Encryptor() = default;
		virtual ~Encryptor() = default;

		std::string getPlainText() const;
		size_t getTextSize() const;
		std::string getEncryptedText() const;
		std::string getDecryptedText() const;

		virtual void setPlainText(const std::string& newPlainText) = 0;

		virtual std::string encrypt() = 0;
		virtual std::string decrypt() = 0;

	protected:
		std::string plainText = "";
		size_t textSize = 0;

		std::string encryptedText = "";
		std::string decryptedText = "";
};
