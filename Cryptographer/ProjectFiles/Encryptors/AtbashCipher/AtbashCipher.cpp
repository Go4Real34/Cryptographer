#include <iostream>
#include <cctype>

#include "AtbashCipher.h"

AtbashCipher::AtbashCipher(const std::string& PlainText) {
	this -> plainText = PlainText;
	this -> textSize = PlainText.size();

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

AtbashCipher::~AtbashCipher() {
}

void AtbashCipher::setPlainText(const std::string& newPlainText) {
	this -> plainText = newPlainText;
	this -> textSize = newPlainText.size();

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

std::string AtbashCipher::encrypt() {
	std::string encryptedText = "";
	for (char& character : this -> plainText) {
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

std::string AtbashCipher::decrypt() {
	std::string decryptedText = "";
	for (char& character : this -> encryptedText) {
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


char AtbashCipher::encryptCharacter(const char& character) {
	const uint8_t indexDifference = this -> getCorrespondingIndexDifference(character, true);

	const uint8_t asciiCodeOfEncryptedCharacter = (islower(character) ? 
													this -> ASCII_CODE_OF_LOWERCASE_Z : this -> ASCII_CODE_OF_UPPERCASE_Z) 
														- indexDifference;

	const char encryptedCharacter = char(asciiCodeOfEncryptedCharacter);
	return encryptedCharacter;
}

char AtbashCipher::decryptCharacter(const char& character) {
	const uint8_t indexDifference = this -> getCorrespondingIndexDifference(character, false);

	const uint8_t asciiCodeOfDecryptedCharacter = (islower(character) ? 
													this -> ASCII_CODE_OF_LOWERCASE_A : ASCII_CODE_OF_UPPERCASE_A) 
														+ indexDifference;

	const char decryptedCharacter = char(asciiCodeOfDecryptedCharacter);
	return decryptedCharacter;
}

uint8_t AtbashCipher::getCorrespondingIndexDifference(const char& character, const bool& isEncrypting) const {
	const uint8_t asciiCodeOfCharacter = uint8_t(character);

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
