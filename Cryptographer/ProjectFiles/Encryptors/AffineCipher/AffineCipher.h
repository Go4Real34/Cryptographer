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

		long long inverseOfAlpha = 1;

		const int8_t englishAlphabetSize = 26;

		const int8_t ASCII_CODE_OF_UPPERCASE_A = 65;
		const int8_t ASCII_CODE_OF_LOWERCASE_A = 97;

		char encryptCharacter(const char& character) const;
		char decryptCharacter(const char& character) const;

		bool areNumbersCoprime(const long long& value1, const int8_t& value2) const;
		long long calculateGreatestCommonDivisor(const long long& dividend, const int8_t& divisor) const;
		int8_t modulus(const long long& divisor, const int8_t& dividend) const;

		long long calculateInverseOfAlpha(const long long& alphaToInverse, const int8_t& modularBase) const;
};
