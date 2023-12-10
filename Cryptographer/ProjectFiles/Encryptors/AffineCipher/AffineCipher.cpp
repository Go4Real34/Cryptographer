#include <iostream>
#include <cctype>

#include "AffineCipher.h"

AffineCipher::AffineCipher(const std::string& PlainText, const long long& Alpha, const long long& Beta) {
	if (Alpha < 1) {
		std::cout << "The alpha value " << Alpha << " is less than 1. Encryption stopped." << std::endl;
	} else if (this -> areNumbersCoprime(Alpha, this -> englishAlphabetSize)) {
		this -> plainText = PlainText;
		this -> textSize = PlainText.size();

		this -> alpha = Alpha;
		this -> beta = this -> modulus(Beta, this -> englishAlphabetSize);

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
	this -> textSize = newPlainText.size();

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

void AffineCipher::setAlpha(const long long& newAlpha) {
	if (newAlpha < 1) {
		std::cout << "The alpha value " << newAlpha << " is less than 1. Encryption stopped." << std::endl;
	} else if (this -> areNumbersCoprime(newAlpha, this -> englishAlphabetSize)) {
		this -> alpha = newAlpha;

		this -> encryptedText = this -> encrypt();
		this -> decryptedText = this -> decrypt();
	} else {
		std::cout << "The alpha value " << newAlpha << " is not coprime with the alphabet size. Encryption stopped." << std::endl;
	}
}

void AffineCipher::setBeta(const long long& newBeta) {
	this -> beta = this -> modulus(newBeta, this -> englishAlphabetSize);

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

std::string AffineCipher::encrypt() {
	std::string encryptedText = "";

	for (const char& character : this -> plainText) {
		if (character == ' ') {
			encryptedText += character;
		} else if (isalpha(character)) {
			encryptedText += this -> encryptCharacter(character);
		} else {
			std::cout << "The character " << character << " is not an alphabetic character. Encryption stopped." << std::endl;
		}
	}

	return encryptedText;
}

std::string AffineCipher::decrypt() {
	this -> inverseOfAlpha = this -> calculateInverseOfAlpha(this -> alpha, this -> englishAlphabetSize);
	
	std::string decryptedText = "";

	for (const char& character : this -> encryptedText) {
		if (character == ' ') {
			decryptedText += character;
		} else if (isalpha(character)) {
			decryptedText += this -> decryptCharacter(character);
		} else {
			std::cout << "The character " << character << " is not an alphabetic character. Decryption stopped." << std::endl;
		}
	}
	
	return decryptedText;
}


char AffineCipher::encryptCharacter(const char& character) const {
	const int8_t asciiCodeOfCharacter = int8_t(character);
	
	const int8_t offsetFromLetterA = asciiCodeOfCharacter - 
										(islower(character) ? 
											this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A);
	
	const int8_t shiftAmount = this -> modulus((this -> alpha * offsetFromLetterA + this -> beta), this -> englishAlphabetSize);
	
	const int8_t asciiCodeOfEncryptedCharacter = ((islower(character) ? 
													this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A) 
														+ shiftAmount);
	
	const char encryptedCharacter = char((asciiCodeOfEncryptedCharacter));
	return encryptedCharacter;
}

char AffineCipher::decryptCharacter(const char& character) const {
	const int8_t asciiCodeOfCharacter = int8_t(character);
	
	const int8_t offsetFromLetterA = asciiCodeOfCharacter - 
										(islower(character) ? 
											this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A);

	const int8_t shiftAmount = this -> modulus(this -> inverseOfAlpha * (offsetFromLetterA - this -> beta), this -> englishAlphabetSize);

	const int8_t asciiCodeOfDecryptedCharacter = (islower(character) ? 
													this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A) 
														+ shiftAmount;

	const char decryptedCharacter = char(asciiCodeOfDecryptedCharacter);
	return decryptedCharacter;
}


bool AffineCipher::areNumbersCoprime(const long long& value1, const int8_t& value2) const {
	return this -> calculateGreatestCommonDivisor(value1, value2) == 1;
}

long long AffineCipher::calculateGreatestCommonDivisor(const long long& dividend, const int8_t& divisor) const {
	if (divisor == 0) {
		return dividend;
	}

	return this -> calculateGreatestCommonDivisor(divisor, this -> modulus(dividend, divisor));
}

int8_t AffineCipher::modulus(const long long& dividend, const int8_t& divisor) const {
	return ((dividend % divisor) + divisor) % divisor;
}

long long AffineCipher::calculateInverseOfAlpha(const long long& alphaToInverse, const int8_t& modularBase) const {
	for (long long inverse = 0; inverse < modularBase; inverse++) {
		if (this -> modulus(alphaToInverse * inverse, modularBase) == 1) {
			return inverse;
		}
	}
	return 1;
}
