#include <iostream>

#include "HillCipher.h"


HillCipher::HillCipher(std::string& PlainText, const std::string& Key) {
	for (size_t index = 0; index < PlainText.size(); index++) {
		if (PlainText[index] == ' ') {
			this -> spaceIndexes.push_back(index);
		}
	}
	PlainText.erase(std::remove(PlainText.begin(), PlainText.end(), ' '), PlainText.end());
	this -> plainText = PlainText;
	this -> textSize = PlainText.size();
	
	if (Key.find(' ') != std::string::npos) {
		std::cout << "The encryption key contains spaces. Encryption stopped." << std::endl;
		
		this -> key = "";
		this -> keySize = 0;
		
		this -> keyMatrix = std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));
		this -> plainTextMatrix = std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));
		this -> plainTextIsLowerMatrix = std::vector<std::vector<bool>>(0, std::vector<bool>(0, false));

		return;
	}

	this -> key = Key;
	this -> keySize = Key.size();
	
	this -> keyMatrix = generateKeyMatrix();
	
	if (!(this -> isKeyValid())) {
		std::cout << "The encryption key is not able to create a matrix that is invertible so, it is not valid. Encryption stopped." << std::endl;

		this -> key = "";
		this -> keySize = 0;
		
		this -> keyMatrix = std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));
		
		this -> plainTextMatrix = std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));
		this -> plainTextIsLowerMatrix = std::vector<std::vector<bool>>(0, std::vector<bool>(0, false));

		this -> encryptedTextMatrix = std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));

		return;
	}
	
	this -> plainTextMatrix = generatePlainTextMatrix();
	this -> plainTextIsLowerMatrix = generatePlainTextIsLowerMatrix();

	this -> encryptedText = encrypt();
	this -> decryptedText = decrypt();
}

HillCipher::~HillCipher() {
}

void HillCipher::setPlainText(std::string& newPlainText) {
	this -> spaceIndexes.clear();
	for (size_t index = 0; index < newPlainText.size(); index++) {
		if (newPlainText[index] == ' ') {
			this -> spaceIndexes.push_back(index);
		}
	}
	newPlainText.erase(std::remove(newPlainText.begin(), newPlainText.end(), ' '), newPlainText.end());
	this -> plainText = newPlainText;
	this -> textSize = newPlainText.size();

	this -> plainTextMatrix = generatePlainTextMatrix();
	this -> plainTextIsLowerMatrix = generatePlainTextIsLowerMatrix();

	this -> encryptedText = encrypt();
	this -> decryptedText = decrypt();
}

void HillCipher::setKey(std::string& newKey) {
	if (newKey.find(' ') == std::string::npos) {
		std::cout << "The encryption key contains spaces. Encryption stopped." << std::endl;

		this -> key = "";
		this -> keySize = 0;
		
		this -> keyMatrix = std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));
		
		this -> plainTextMatrix = std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));
		this -> plainTextIsLowerMatrix = std::vector<std::vector<bool>>(0, std::vector<bool>(0, false));
		
		this -> encryptedTextMatrix = std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));
		
		return;
	}

	this -> key = newKey;
	this -> keySize = newKey.size();

	this -> keyMatrix = generateKeyMatrix();

	if (!(this -> isKeyValid())) {
		std::cout << "The encryption key is not able to create a matrix that is invertible so, it is not valid. Encryption stopped." << std::endl;

		this -> key = "";
		this -> keySize = 0;

		this -> keyMatrix = std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));
		this -> plainTextMatrix = std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));
		this -> plainTextIsLowerMatrix = std::vector<std::vector<bool>>(0, std::vector<bool>(0, false));

		return;
	}

	this -> encryptedText = encrypt();
	this -> decryptedText = decrypt();
}

std::string HillCipher::encrypt() {
	if (this -> keySize == 0) {
		std::cout << "The encryption key is empty. Encryption stopped." << std::endl;
		return "";
	}

	this -> encryptedTextMatrix = multiplyMatrices(this -> keyMatrix, this -> plainTextMatrix);
	const size_t encryptedTextMatrixRowSize = this -> encryptedTextMatrix.size();
	const size_t encryptedTextMatrixColumnSize = this -> encryptedTextMatrix[0].size();
	std::string matrixText = "";

	for (size_t column = 0; column < encryptedTextMatrixColumnSize; column++) {
		for (size_t row = 0; row < encryptedTextMatrixRowSize; row++) {
			const int8_t numericalValueOfCharacter = this -> encryptedTextMatrix[row][column];
			const bool isCharacterLower = this -> plainTextIsLowerMatrix[row][column];
			
			const int8_t asciiCodeOfCharacter = numericalValueOfCharacter + (isCharacterLower ? this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A);
			const char character = char(asciiCodeOfCharacter);
			matrixText += character;
		}
	}

	std::string encryptedText = "";
	int64_t spaceCount = 0;
	for (size_t matrixTextIndex = 0, spaceIndex = 0; matrixTextIndex < matrixText.size() + this -> spaceIndexes.size(); matrixTextIndex++) {
		if (spaceIndex < this -> spaceIndexes.size() && matrixTextIndex == this -> spaceIndexes[spaceIndex] + spaceCount) {
			encryptedText += ' ';
			spaceCount++;
			spaceIndex++;
		} else {
			encryptedText += matrixText[matrixTextIndex - spaceCount];
		}
	}

	return encryptedText;
}


std::vector<std::vector<int8_t>> HillCipher::generateKeyMatrix() const {
	if (this -> keySize == 0) {
		std::cout << "The encryption key is empty. Matrix generation stopped." << std::endl;
		return std::vector<std::vector<int8_t>>(0, std::vector<int8_t>(0, 0));
	}

	const int64_t matrixSize = this -> getNearestSquareNumberOfKeyLength();
	
	int8_t temporaryNumericValueForOverflow = 0;
	size_t indexOfKey = 0;

	std::vector<std::vector<int8_t>> keyMatrix(matrixSize, std::vector<int8_t>(matrixSize, 0));
	for (int64_t row = 0; row < matrixSize; row++) {
		for (int64_t column = 0; column < matrixSize; column++) {
			if (indexOfKey < this -> keySize) {
				const char character = this -> key[indexOfKey];
				keyMatrix[row][column] = int8_t(character - (islower(character) ? this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A));
				indexOfKey++;
			} else {
				keyMatrix[row][column] = temporaryNumericValueForOverflow;
				temporaryNumericValueForOverflow = (temporaryNumericValueForOverflow + 1) % this -> englishAlphabetSize;
			}
		}
	}

	return keyMatrix;
}

std::vector<std::vector<int8_t>> HillCipher::generatePlainTextMatrix() const {
	const int64_t keyMatrixSize = this -> keyMatrix.size();
	const int64_t numberOfColumns = int64_t(ceil(double(this -> textSize) / keyMatrixSize));

	std::vector<std::vector<int8_t>> plainTextMatrix(keyMatrixSize, std::vector<int8_t>(numberOfColumns, 0));
	size_t indexOfPlainText = 0;

	for (int64_t column = 0; column < numberOfColumns; column++) {
		for (int64_t row = 0; row < keyMatrixSize; row++) {
			if (indexOfPlainText < this -> textSize) {
				const char character = this -> plainText[indexOfPlainText];
				plainTextMatrix[row][column] = int8_t(character - (islower(character) ? this -> ASCII_CODE_OF_LOWERCASE_A : this -> ASCII_CODE_OF_UPPERCASE_A));
				indexOfPlainText++;
			} else {
				plainTextMatrix[row][column] = int8_t('x') - this -> ASCII_CODE_OF_LOWERCASE_A;
			}
		}
	}
	return plainTextMatrix;
}

std::vector<std::vector<bool>> HillCipher::generatePlainTextIsLowerMatrix() const {
	const int64_t keyMatrixSize = this -> keyMatrix.size();
	const int64_t numberOfColumns = int64_t(ceil(double(this -> textSize) / keyMatrixSize));

	std::vector<std::vector<bool>> plainTextIsLowerMatrix(keyMatrixSize, std::vector<bool>(numberOfColumns, false));
	size_t indexOfPlainText = 0;

	for (int64_t column = 0; column < numberOfColumns; column++) {
		for (int64_t row = 0; row < keyMatrixSize; row++) {
			if (indexOfPlainText < this -> textSize) {
				const char character = this -> plainText[indexOfPlainText];
				plainTextIsLowerMatrix[row][column] = bool(islower(character));
				indexOfPlainText++;
			} else {
				plainTextIsLowerMatrix[row][column] = true;
			}
		}
	}
	return plainTextIsLowerMatrix;
}

int64_t HillCipher::getNearestSquareNumberOfKeyLength() const {
	const long double squareRootOfKeySize = sqrt(this -> keySize);
	return (squareRootOfKeySize - uint64_t(squareRootOfKeySize) == 0) ? uint64_t(squareRootOfKeySize) : uint64_t(squareRootOfKeySize) + 1;
}

bool HillCipher::isKeyValid() {
	return getDeterminantOfMatrix(this -> keyMatrix) != 0;
}

int64_t HillCipher::getDeterminantOfMatrix(std::vector<std::vector<int8_t>>& matrix) const {
	const size_t matrixSize = matrix.size();
    int64_t determinant = 0;

    if (matrixSize == 1) {
        return matrix[0][0];
    } else if (matrixSize == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    } else {
        for (size_t topRowPosition = 0; topRowPosition < matrixSize; topRowPosition++) {
            std::vector<std::vector<int8_t>> subMatrix(matrixSize - 1, std::vector<int8_t>(matrixSize - 1, 0));

            for (size_t mainMatrixRow = 1; mainMatrixRow < matrixSize; mainMatrixRow++) {
                const size_t subMatrixRow = mainMatrixRow - 1;
                for (size_t mainMatrixColumn = 0, subMatrixColumn = 0; mainMatrixColumn < matrixSize; mainMatrixColumn++) {
                    if (mainMatrixColumn == topRowPosition) {
                        continue;
                    }
                    subMatrix[subMatrixRow][subMatrixColumn] = matrix[mainMatrixRow][mainMatrixColumn];
                    subMatrixColumn++;
                }
            }
            
			determinant += (topRowPosition % 2 == 0 ? 1 : -1) * matrix[0][topRowPosition] * getDeterminantOfMatrix(subMatrix);
        }
    }

    return determinant;
}

std::vector<std::vector<int8_t>> HillCipher::multiplyMatrices(std::vector<std::vector<int8_t>>& matrix1, std::vector<std::vector<int8_t>>& matrix2) const {
	const size_t matrix1RowCount = matrix1.size();
	const size_t matrix1ColumnCount = matrix1[0].size();
	const size_t matrix2ColumnCount = matrix2[0].size();

	std::vector<std::vector<int8_t>> resultMatrix(matrix1RowCount, std::vector<int8_t>(matrix2ColumnCount, 0));

	for (size_t firstMatrixRow = 0; firstMatrixRow < matrix1RowCount; firstMatrixRow++) {
		for (size_t secondMatrixColumn = 0; secondMatrixColumn < matrix2ColumnCount; secondMatrixColumn++) {
			for (size_t firstMatrixColumn = 0; firstMatrixColumn < matrix1ColumnCount; firstMatrixColumn++) {
				resultMatrix[firstMatrixRow][secondMatrixColumn] += (matrix1[firstMatrixRow][firstMatrixColumn] * matrix2[firstMatrixColumn][secondMatrixColumn]) % this -> englishAlphabetSize;
			}
			resultMatrix[firstMatrixRow][secondMatrixColumn] %= this -> englishAlphabetSize;
		}
	}

	return resultMatrix;
}
