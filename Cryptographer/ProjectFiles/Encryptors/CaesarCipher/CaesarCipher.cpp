#include <iostream>
#include <cctype>

#include "CaesarCipher.h"

CaesarCipher::CaesarCipher(const std::string& PlainText, const long long& ShiftAmount) {
	this -> plainText = PlainText;
	this -> textSize = PlainText.size();

	this -> shiftAmount = this -> modulus(ShiftAmount, this -> englishAlphabetSize);

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

CaesarCipher::~CaesarCipher() {
}

void CaesarCipher::setPlainText(const std::string& newPlainText) {
	this -> plainText = newPlainText;
	this -> textSize = newPlainText.size();

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

void CaesarCipher::setShiftAmount(uint8_t newShiftAmount) {
	this -> shiftAmount = this -> modulus(newShiftAmount, this -> englishAlphabetSize);

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

std::string CaesarCipher::encrypt() {
	std::string encryptedText = "";

	for (const char& character : this -> plainText) {
		if (character == ' ') {
			encryptedText += character;
		} else if (isalpha(character)) {
			encryptedText += this -> encryptCharacter(character);
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
			decryptedText += this -> decryptCharacter(character);
		} else {
			std::cout << "The character " << character << " is not an alphabetic character. Decryption stopped." << std::endl;
			break;
		}
	}
	
	return decryptedText;
}


char CaesarCipher::encryptCharacter(const char& character) {
	const uint8_t asciiValueOfCharacter = uint8_t(character);
	
	const uint8_t asciiCodeOfShiftedEncryptedCharacter = asciiValueOfCharacter + this -> shiftAmount;
	const uint8_t  asciiCodeOfEncryptedCharacter = islower(character) ?
													(asciiCodeOfShiftedEncryptedCharacter > this -> ASCII_CODE_OF_LOWERCASE_Z ?
														asciiCodeOfShiftedEncryptedCharacter - this -> englishAlphabetSize : asciiCodeOfShiftedEncryptedCharacter) 
													:
													(asciiCodeOfShiftedEncryptedCharacter > ASCII_CODE_OF_UPPERCASE_Z ? 
														asciiCodeOfShiftedEncryptedCharacter - this -> englishAlphabetSize : asciiCodeOfShiftedEncryptedCharacter);

	const char encryptedCharacter = char(asciiCodeOfEncryptedCharacter);
	return encryptedCharacter;
}

char CaesarCipher::decryptCharacter(const char& character) {
	const uint8_t asciiValueOfCharacter = uint8_t(character);

	const uint8_t asciiCodeOfShiftedDecryptedCharacter = asciiValueOfCharacter - this -> shiftAmount;
	const uint8_t asciiCodeOfDecryptedCharacter = islower(character) ? 
													(asciiCodeOfShiftedDecryptedCharacter < this -> ASCII_CODE_OF_LOWERCASE_A ? 
														asciiCodeOfShiftedDecryptedCharacter + this -> englishAlphabetSize : asciiCodeOfShiftedDecryptedCharacter) 
													:
													(asciiCodeOfShiftedDecryptedCharacter < this -> ASCII_CODE_OF_UPPERCASE_A ? 
														asciiCodeOfShiftedDecryptedCharacter + this -> englishAlphabetSize : asciiCodeOfShiftedDecryptedCharacter);

	const char decryptedCharacter = char(asciiCodeOfDecryptedCharacter);
	return decryptedCharacter;
}

uint8_t CaesarCipher::modulus(const long long& dividend, const uint8_t& divisor) const {
	return ((dividend % divisor) + divisor) % divisor;
}
