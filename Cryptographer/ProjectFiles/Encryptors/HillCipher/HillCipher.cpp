#include <iostream>

#include "HillCipher.h"

HillCipher::HillCipher(const std::string& PlainText, const std::string& Key) {
	this -> plainText = PlainText;
	this -> textSize = PlainText.size();
	
	this -> key = Key;
	this -> keySize = Key.size();
	
	this -> keyMatrix = generateKeyMatrix();
	
	if (this -> isKeyValid()) {
		this -> plainTextMatrix = generatePlainTextMatrix();
		this -> plainTextIsLowerMatrix = generatePlainTextIsLowerMatrix();

		this -> encryptedText = encrypt();
		this -> decryptedText = decrypt();
	} else {
		std::cout << "The encryption key is not able to create a matrix that is invertible so, it is not valid. Encryption stopped." << std::endl;
	}
}

HillCipher::~HillCipher() {
}

void HillCipher::setPlainText(const std::string& newPlainText) {
	this -> plainText = newPlainText;
	this -> textSize = newPlainText.size();

	this -> plainTextMatrix = generatePlainTextMatrix();
	this -> plainTextIsLowerMatrix = generatePlainTextIsLowerMatrix();

	this -> encryptedText = encrypt();
	this -> decryptedText = decrypt();
}

void HillCipher::setKey(const std::string& newKey) {
	this -> key = newKey;
	this -> keySize = newKey.size();

	this -> keyMatrix = generateKeyMatrix();

	if (this -> isKeyValid()) {
		this -> encryptedText = encrypt();
		this -> decryptedText = decrypt();
	} else {
		std::cout << "The encryption key is not able to create a matrix that is invertible so, it is not valid. Encryption stopped." << std::endl;
	}
}


std::vector<std::vector<int8_t>> HillCipher::generateKeyMatrix() const {
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
