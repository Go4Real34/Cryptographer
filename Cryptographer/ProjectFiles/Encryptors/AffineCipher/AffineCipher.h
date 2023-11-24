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

		uint8_t englishAlphabetSize = 26;

		char encryptCharacter(const char& character) const override;
		char decryptCharacter(const char& character) const override;

		bool areNumbersCoprime(const long long& value1, const long long& value2) const;
		long long calculateGreatestCommonDivisor(const long long& dividend, const long long& divisor) const;
		long long modulus(const long long& divisor, const long long& dividend) const;
};
