#include "Encryptor.h"

std::string Encryptor::getPlainText() const {
	return this -> plainText;
}

size_t Encryptor::getTextSize() const {
	return this -> textSize;
}

std::string Encryptor::getEncryptedText() const {
	return this -> encryptedText;
}

std::string Encryptor::getDecryptedText() const {
	return this -> decryptedText;
}
