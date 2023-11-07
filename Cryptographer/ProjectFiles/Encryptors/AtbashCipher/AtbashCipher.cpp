#include <string>

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
