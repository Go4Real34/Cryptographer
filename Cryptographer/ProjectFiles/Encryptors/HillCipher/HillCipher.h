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
		std::vector<std::vector<long double>> inverseKeyMatrix;
		
		std::vector<std::vector<int8_t>> plainTextMatrix;
		std::vector<std::vector<bool>> plainTextIsLowerMatrix;

		std::vector<size_t> spaceIndexes;

		std::vector<std::vector<int8_t>> encryptedTextMatrix;
		std::vector<std::vector<int8_t>> decryptedTextMatrix;
		
		std::vector<std::vector<int8_t>> generateKeyMatrix() const;
		std::vector<std::vector<int8_t>> generatePlainTextMatrix() const;
		std::vector<std::vector<bool>> generatePlainTextIsLowerMatrix() const;

		int64_t getNearestSquareNumberOfKeyLength() const;

		bool isKeyValid();
		int64_t getDeterminantOfMatrix(std::vector<std::vector<int8_t>>& matrix) const;

		template<typename TParameter, typename TResult>
		std::vector<std::vector<TResult>> multiplyMatrices(std::vector<std::vector<TParameter>>& matrix1, std::vector<std::vector<int8_t>>& matrix2, const TResult& divisor) const;

		std::vector<std::vector<long double>> calculateMatrixInverseWithGaussJordanElimination(std::vector<std::vector<int8_t>>& matrix) const;
		
		template <typename TResult, typename TParameter>
		TResult modulus(const TResult& dividend, const TParameter& divisor) const;
};
