#include "VigenereCipher.h"

VigenereCipher::VigenereCipher(const std::string& PlainText, const std::string& Key) {
	this -> plainText = PlainText;
	this -> textSize = PlainText.size();
	this -> key = Key;
	this -> keySize = Key.size();

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

	this -> encryptedText = this -> encrypt();
	this -> decryptedText = this -> decrypt();
}
