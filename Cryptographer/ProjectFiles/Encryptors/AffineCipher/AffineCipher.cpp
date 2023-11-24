#include <iostream>
#include <cctype>

#include "AffineCipher.h"

AffineCipher::AffineCipher(const std::string& PlainText, const long long& Alpha, const long long& Beta) {
	if (Alpha < 1) {
		std::cout << "The alpha value " << Alpha << " is less than 1. Encryption stopped." << std::endl;
	} else if (areNumbersCoprime(Alpha, this -> englishAlphabetSize)) {
		this -> plainText = PlainText;

		this -> alpha = Alpha;
		this -> beta = modulus(Beta, this -> englishAlphabetSize);

		this -> encryptedText = this -> encrypt();
		this -> decryptedText = this -> decrypt();
	} else {
		std::cout << "The alpha value " << Alpha << " is not coprime with the alphabet size. Encryption stopped." << std::endl;
	}
}

AffineCipher::~AffineCipher() {
}

void AffineCipher::setPlainText(const std::string& newPlainText) {
	this -> plainText = newPlainText;

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

void AffineCipher::setAlpha(const long long& newAlpha) {
	if (newAlpha < 1) {
		std::cout << "The alpha value " << newAlpha << " is less than 1. Encryption stopped." << std::endl;
	} else if (areNumbersCoprime(newAlpha, this -> englishAlphabetSize)) {
		this -> alpha = newAlpha;

		this -> encryptedText = this -> encrypt();
		this -> decryptedText = this -> decrypt();
	} else {
		std::cout << "The alpha value " << newAlpha << " is not coprime with the alphabet size. Encryption stopped." << std::endl;
	}
}

void AffineCipher::setBeta(const long long& newBeta) {
	this -> beta = modulus(newBeta, this -> englishAlphabetSize);

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}


bool AffineCipher::areNumbersCoprime(const long long& value1, const long long& value2) const {
	return calculateGreatestCommonDivisor(value1, value2) == 1;
}

long long AffineCipher::calculateGreatestCommonDivisor(const long long& dividend, const long long& divisor) const {
	if (divisor == 0) {
		return dividend;
	}

	return calculateGreatestCommonDivisor(divisor, modulus(dividend, divisor));
}

long long AffineCipher::modulus(const long long& dividend, const long long& divisor) const {
	return ((dividend % divisor) + divisor) % divisor;
}
