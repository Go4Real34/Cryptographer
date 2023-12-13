#include <iostream>

#include "VigenereCipher.h"

VigenereCipher::VigenereCipher(const std::string& PlainText, const std::string& Key) {
	this -> plainText = PlainText;
	this -> textSize = PlainText.size();

	this -> key = Key;
	this -> keySize = Key.size();

	this -> equalizedKey = this -> createEqualSizedKey();
	this -> equalizedKeySize = this -> equalizedKey.size();

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

VigenereCipher::~VigenereCipher() {
}

void VigenereCipher::setPlainText(const std::string& newPlainText) {
	this -> plainText = newPlainText;
	this -> textSize = newPlainText.size();

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

void VigenereCipher::setKey(const std::string& newKey) {
	this -> key = newKey;
	this -> keySize = newKey.size();

	this -> equalizedKey = this -> createEqualSizedKey();
	this -> equalizedKeySize = this -> equalizedKey.size();

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}

std::string VigenereCipher::encrypt() {
	std::string encryptedText = "";
	for (size_t i = 0; i < this -> textSize; i++) {
		const char currentCharacter = this -> plainText[i];
		const char currentKeyCharacter = this -> equalizedKey[i];

		if (currentCharacter == ' ') {
			encryptedText += currentCharacter;
		} else if (isalpha(currentCharacter)) {
			encryptedText += this -> encryptCharacter(currentCharacter, currentKeyCharacter);
		} else {
			std::cout << "The character " << currentCharacter << " is not an alphabetic character. Encryption stopped." << std::endl;
		}
	}

	return encryptedText;
}

std::string VigenereCipher::decrypt() {
	std::string decryptedText = "";
	for (size_t i = 0; i < this -> encryptedText.size(); i++) {
		const char currentCharacter = this -> encryptedText[i];
		const char currentKeyCharacter = this -> equalizedKey[i];
		
		if (currentCharacter == ' ') {
			decryptedText += currentCharacter;
		} else if (isalpha(currentCharacter)) {
			decryptedText += this -> decryptCharacter(currentCharacter, currentKeyCharacter);
		} else {
			std::cout << "The character " << currentCharacter << " is not an alphabetic character. Decryption stopped." << std::endl;
		}
	}

	return decryptedText;
}


char VigenereCipher::encryptCharacter(const char& textCharacter, const char& keyCharacter) const {
	const bool isTextCharacterLowerCase = islower(textCharacter);
	const bool isKeyCharacterLowerCase = islower(keyCharacter);

	const int8_t textCharacterAlphabetIndex = this -> getAlphabetIndex(textCharacter, isTextCharacterLowerCase);
	const int8_t keyCharacterAlphabetIndex = this -> getAlphabetIndex(keyCharacter, isKeyCharacterLowerCase);

	const int8_t encryptedCharacterAlphabetIndex = this -> modulus(textCharacterAlphabetIndex + keyCharacterAlphabetIndex, this -> englishAlphabetSize);
	const char encryptedCharacter = this -> getAlphabetCharacter(encryptedCharacterAlphabetIndex, isTextCharacterLowerCase);
	return encryptedCharacter;
}

char VigenereCipher::decryptCharacter(const char& textCharacter, const char& keyCharacter) const {
	const bool isTextCharacterLowerCase = islower(textCharacter);
	const bool isKeyCharacterLowerCase = islower(keyCharacter);

	const int8_t textCharacterAlphabetIndex = this -> getAlphabetIndex(textCharacter, isTextCharacterLowerCase);
	const int8_t keyCharacterAlphabetIndex = this -> getAlphabetIndex(keyCharacter, isKeyCharacterLowerCase);

	const int8_t decryptedCharacterAlphabetIndex = this -> modulus(textCharacterAlphabetIndex - keyCharacterAlphabetIndex, this -> englishAlphabetSize);
	const char decryptedCharacter = this -> getAlphabetCharacter(decryptedCharacterAlphabetIndex, isTextCharacterLowerCase);
	return decryptedCharacter;
}

std::string VigenereCipher::createEqualSizedKey() const {
	std::string equalKey = this -> key;
	size_t spaceCount = 0;

	for (size_t i = this -> keySize; i < this -> textSize; i++) {
		const char currentCharacter = this -> plainText[i];
		if (currentCharacter == ' ') {
			equalKey += currentCharacter;
			spaceCount++;
			continue;
		}
		equalKey += this -> key[this -> modulus(int8_t(i - spaceCount), int8_t(this -> keySize))];
	}

	return equalKey;
}

int8_t VigenereCipher::getAlphabetIndex(const char& character, const bool& isLowerCase) const {
	int8_t asciiCodeOfCharacter = int8_t(character);

	int8_t alphabetIndex = asciiCodeOfCharacter - 
								(isLowerCase ? 
									this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A);

	return alphabetIndex;
}

char VigenereCipher::getAlphabetCharacter(const int8_t& alphabetIndex, const bool& isLowerCase) const {
	int8_t asciiCodeOfCharacter = alphabetIndex + 
										(isLowerCase ?
											this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A);

	char character = char(asciiCodeOfCharacter);
	return character;
}

int8_t VigenereCipher::modulus(const int8_t& dividend, const int8_t& divisor) const {
	return ((dividend % divisor) + divisor) % divisor;
}
