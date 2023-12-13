#include <iostream>

#include "ProjectFiles/Encryptors/AtbashCipher/AtbashCipher.h"
#include "ProjectFiles/Encryptors/CaesarCipher/CaesarCipher.h"
#include "ProjectFiles/Encryptors/AffineCipher/AffineCipher.h"
#include "ProjectFiles/Encryptors/VigenereCipher/VigenereCipher.h"
#include "ProjectFiles/Encryptors/HillCipher/HillCipher.h"

int main() {
	std::string text = "Hello world";

	int alpha = 3;
	int beta = 5;

	std::string key = "key";

	AtbashCipher atbashCipher = AtbashCipher(text);
	CaesarCipher caesarCipher = CaesarCipher(text, alpha);
	AffineCipher affineCipher = AffineCipher(text, alpha, beta);
	VigenereCipher vigenereCipher = VigenereCipher(text, key);
	HillCipher hillCipher = HillCipher(text, key);

	std::cout << "Atbash cipher encrypt: " << atbashCipher.encrypt() << '\n'
				<< "Atbash cipher decrypt: " << atbashCipher.decrypt() << std::endl << std::endl;

	std::cout << "Caesar cipher encrypt: " << caesarCipher.encrypt() << '\n'
				<< "Caesar cipher decrypt: " << caesarCipher.decrypt() << std::endl << std::endl;

	std::cout << "Affine cipher encrypt: " << affineCipher.encrypt() << '\n'
				<< "Affine cipher decrypt: " << affineCipher.decrypt() << std::endl << std::endl;

	std::cout << "Vigenere cipher encrypt: " << vigenereCipher.encrypt() << '\n'
				<< "Vigenere cipher decrypt: " << vigenereCipher.decrypt() << std::endl << std::endl;

	std::cout << "Hill cipher encrypt: " << hillCipher.encrypt() << '\n'
				<< "Hill cipher decrypt (under bug fix - not implemented correctly): " << hillCipher.decrypt() << std::endl;

	return 0;
}
