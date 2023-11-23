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
