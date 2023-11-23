#include <iostream>
#include <cctype>

#include "CaesarCipher.h"

CaesarCipher::CaesarCipher(const std::string& PlainText, uint8_t ShiftAmount) {
	this -> plainText = PlainText;
	this -> textSize = PlainText.size();

	this -> shiftAmount = ShiftAmount % this -> englishAlphabetSize;

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
	this -> shiftAmount = newShiftAmount;

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