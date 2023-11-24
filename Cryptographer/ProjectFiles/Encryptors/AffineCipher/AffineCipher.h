#pragma once

#include "../Encryptor.h"

class AffineCipher : public Encryptor {
	public:
		AffineCipher(const std::string& PlainText, const long long& Alpha, const long long& Beta);
		~AffineCipher();

		void setPlainText(const std::string& newPlainText) override;
		void setAlpha(const long long& newAlpha);
		void setBeta(const long long& newBeta);

		std::string encrypt() override;
		std::string decrypt() override;

	private:
		long long alpha = 1;
		long long beta = 0;

		char encryptCharacter(const char& character) const override;
		char decryptCharacter(const char& character) const override;
};
