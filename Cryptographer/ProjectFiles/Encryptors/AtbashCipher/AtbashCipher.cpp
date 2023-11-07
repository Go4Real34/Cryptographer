#include <string>
#include <cctype>
#include <iostream>

#include "AtbashCipher.h"

AtbashCipher::AtbashCipher(const std::string& PlainText) {
	this -> plainText = PlainText;
	this -> textSize = PlainText.size();

	this -> encryptedText = encrypt();
	this -> decryptedText = decrypt();
}

AtbashCipher::~AtbashCipher() {
}

void AtbashCipher::setPlainText(const std::string& newPlainText) {
	this -> plainText = newPlainText;
	this -> textSize = newPlainText.size();
	this -> encryptedText = encrypt();
	this -> decryptedText = decrypt();
}

std::string AtbashCipher::encrypt() {
	std::string encryptedText = "";
	for (char& character : this -> plainText) {
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


char AtbashCipher::encryptCharacter(const char& character) const {
	const int indexDifference = getCorrespondingIndexDifference(character);

	const int asciiCodeOfEncryptedCharacter = (islower(character) ? 
												this -> ASCII_CODE_OF_LOWERCASE_Z : this -> ASCII_CODE_OF_UPPERCASE_Z) 
													- indexDifference;

	char encryptedCharacter = char(asciiCodeOfEncryptedCharacter);

	return encryptedCharacter;
}

int AtbashCipher::getCorrespondingIndexDifference(const char& character) const {
	const int asciiCodeOfCharacter = int(character);

	const int indexDifference = asciiCodeOfCharacter - 
									(islower(character) ? 
										this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A);

	return indexDifference;
}
