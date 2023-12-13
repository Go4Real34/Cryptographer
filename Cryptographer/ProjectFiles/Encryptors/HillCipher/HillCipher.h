#pragma once

#include <vector>

#include "../Encryptor.h"

class HillCipher : public Encryptor {
	public:
		HillCipher(std::string& PlainText, const std::string& Key);
		~HillCipher();

		void setPlainText(std::string& newPlainText);
		void setKey(std::string& newKey);

		std::string encrypt() override;
		std::string decrypt() override;

	private:
		std::string key = "";
		size_t keySize = 0;

		const int8_t ASCII_CODE_OF_UPPERCASE_A = 65;
		const int8_t ASCII_CODE_OF_LOWERCASE_A = 97;

		const int8_t englishAlphabetSize = 26;

		std::vector<std::vector<int8_t>> keyMatrix;
		
		std::vector<std::vector<int8_t>> plainTextMatrix;
		std::vector<std::vector<bool>> plainTextIsLowerMatrix;

		std::vector<size_t> spaceIndexes;

		std::vector<std::vector<int8_t>> encryptedTextMatrix;
		
		std::vector<std::vector<int8_t>> generateKeyMatrix() const;
		std::vector<std::vector<int8_t>> generatePlainTextMatrix() const;
		std::vector<std::vector<bool>> generatePlainTextIsLowerMatrix() const;

		int64_t getNearestSquareNumberOfKeyLength() const;

		bool isKeyValid();
		int64_t getDeterminantOfMatrix(std::vector<std::vector<int8_t>>& matrix) const;

		std::vector<std::vector<int8_t>> multiplyMatrices(std::vector<std::vector<int8_t>>& matrix1, std::vector<std::vector<int8_t>>& matrix2) const;
};
