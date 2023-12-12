#pragma once

#include <vector>

#include "../Encryptor.h"

class HillCipher : public Encryptor {
	public:
		HillCipher(const std::string& PlainText, const std::string& Key);
		~HillCipher();

		void setPlainText(const std::string& newPlainText) override;
		void setKey(const std::string& newKey);

		std::string encrypt() override;
		std::string decrypt() override;

	private:
		std::string key = "";
		size_t keySize = 0;

		const int8_t englishAlphabetSize = 26;

		std::vector<std::vector<int8_t>> keyMatrix;
		
		std::vector<std::vector<int8_t>> plainTextMatrix;
		std::vector<std::vector<bool>> plainTextIsLowerMatrix;
		
		std::vector<std::vector<int8_t>> generateKeyMatrix() const;
		std::vector<std::vector<int8_t>> generatePlainTextMatrix() const;
		std::vector<std::vector<bool>> generatePlainTextIsLowerMatrix() const;

		int64_t getNearestSquareNumberOfKeyLength() const;

		bool isKeyValid() const;
		int64_t getDeterminantOfMatrix(std::vector<std::vector<int64_t>>& matrix) const;
};
