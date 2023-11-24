#include <iostream>
#include <cctype>

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

std::string AtbashCipher::decrypt() {
	std::string decryptedText = "";
	for (char& character : this -> encryptedText) {
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


char AtbashCipher::encryptCharacter(const char& character) const {
	const uint8_t indexDifference = getCorrespondingIndexDifference(character, true);

	const uint8_t asciiCodeOfEncryptedCharacter = (islower(character) ? 
													this -> ASCII_CODE_OF_LOWERCASE_Z : this -> ASCII_CODE_OF_UPPERCASE_Z) 
														- indexDifference;

	char encryptedCharacter = char(asciiCodeOfEncryptedCharacter);
	return encryptedCharacter;
}

char AtbashCipher::decryptCharacter(const char& character) const {
	const uint8_t indexDifference = getCorrespondingIndexDifference(character, false);

	const uint8_t asciiCodeOfEncryptedCharacter = (islower(character) ? 
													this -> ASCII_CODE_OF_LOWERCASE_A : ASCII_CODE_OF_UPPERCASE_A) 
														+ indexDifference;

	char decryptedCharacter = char(asciiCodeOfEncryptedCharacter);
	return decryptedCharacter;
}

uint8_t AtbashCipher::getCorrespondingIndexDifference(const char& character, const bool& isEncrypting) const {
	const int asciiCodeOfCharacter = uint8_t(character);

	const uint8_t indexDifference = isEncrypting ? 
										(asciiCodeOfCharacter - 
											(islower(character) ? 
												this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A)) 
									: 
									((islower(character) ? 
										this -> ASCII_CODE_OF_LOWERCASE_Z : this -> ASCII_CODE_OF_UPPERCASE_Z) 
											- asciiCodeOfCharacter);

	return indexDifference;
}
