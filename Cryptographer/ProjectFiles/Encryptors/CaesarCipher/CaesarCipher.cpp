#include <iostream>
#include <cctype>

#include "CaesarCipher.h"

CaesarCipher::CaesarCipher(const std::string& PlainText, long long& ShiftAmount) {
	this -> plainText = PlainText;
	this -> textSize = PlainText.size();

	this -> shiftAmount = modulus(ShiftAmount, this -> englishAlphabetSize);

	this -> encryptedText = encrypt();
	this -> decryptedText = decrypt();
}

CaesarCipher::~CaesarCipher() {
}

void CaesarCipher::setPlainText(const std::string& newPlainText) {
	this -> plainText = newPlainText;
	this -> textSize = newPlainText.size();

	this -> encryptedText = encrypt();
	this -> decryptedText = decrypt();
}

void CaesarCipher::setShiftAmount(uint8_t newShiftAmount) {
	this -> shiftAmount = modulus(newShiftAmount, this -> englishAlphabetSize);

	this -> encryptedText = encrypt();
	this -> decryptedText = decrypt();
}

std::string CaesarCipher::encrypt() {
	std::string encryptedText = "";

	for (const char& character : this -> plainText) {
		if (character == ' ') {
			encryptedText += character;
		} else if (isalpha(character)) {
			encryptedText += encryptCharacter(character);
		} else {
			std::cout << "The character " << character << " is not an alphabetic character. Encryption stopped." << std::endl;
			break;
		}
	}

	return encryptedText;
}

std::string CaesarCipher::decrypt() {
	std::string decryptedText = "";

	for (const char& character : this -> encryptedText) {
		if (character == ' ') {
			decryptedText += character;
		} else if (isalpha(character)) {
			decryptedText += decryptCharacter(character);
		} else {
			std::cout << "The character " << character << " is not an alphabetic character. Decryption stopped." << std::endl;
			break;
		}
	}
	
	return decryptedText;
}


char CaesarCipher::encryptCharacter(const char& character) const {
	uint8_t asciiValueOfCharacter = uint8_t(character);
	
	uint8_t asciiCodeOfEncryptedCharacter = asciiValueOfCharacter + this -> shiftAmount;
	asciiCodeOfEncryptedCharacter = islower(character) ?
										(asciiCodeOfEncryptedCharacter > this -> ASCII_CODE_OF_LOWERCASE_Z ?
											asciiCodeOfEncryptedCharacter - this -> englishAlphabetSize : asciiCodeOfEncryptedCharacter) 
									:
									(asciiCodeOfEncryptedCharacter > ASCII_CODE_OF_UPPERCASE_Z ? 
										asciiCodeOfEncryptedCharacter - this -> englishAlphabetSize : asciiCodeOfEncryptedCharacter);

	char encryptedCharacter = char(asciiCodeOfEncryptedCharacter);
	return encryptedCharacter;
}

char CaesarCipher::decryptCharacter(const char& character) const {
	uint8_t asciiValueOfCharacter = uint8_t(character);

	uint8_t asciiCodeOfDecryptedCharacter = asciiValueOfCharacter - this -> shiftAmount;
	asciiCodeOfDecryptedCharacter = islower(character) ? 
										(asciiCodeOfDecryptedCharacter < this -> ASCII_CODE_OF_LOWERCASE_A ? 
											asciiCodeOfDecryptedCharacter + this -> englishAlphabetSize : asciiCodeOfDecryptedCharacter) 
									:
									(asciiCodeOfDecryptedCharacter < this -> ASCII_CODE_OF_UPPERCASE_A ? 
										asciiCodeOfDecryptedCharacter + this -> englishAlphabetSize : asciiCodeOfDecryptedCharacter);

	char decryptedCharacter = char(asciiCodeOfDecryptedCharacter);
	return decryptedCharacter;
}

uint8_t CaesarCipher::modulus(const long long& dividend, const uint8_t& divisor) const {
	return ((dividend % divisor) + divisor) % divisor;
}
