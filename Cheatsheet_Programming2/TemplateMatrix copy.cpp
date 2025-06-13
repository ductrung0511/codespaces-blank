#include<iostream>
#include <cassert>
#include <cmath>
using namespace std;

template <typename T>
class Matrix {
    private:
        T** data;
        size_t numCol;
        size_t numRow;    
    public:
        Matrix(size_t row, size_t col ) : numCol(col), numRow(row) {
            assert(col > 0 && row > 0); // Ensure dimensions are positive
            data = new T*[row];
            for (size_t i = 0; i < row; ++i) {
                data[i] = new T[col](); // Allocate memory for each row to 0 
            }
        }

        ~Matrix() {
            for (size_t i = 0; i < numRow; ++i) {
                delete[] data[i]; // Delete each row
            }
            delete[] data;
        }

        T& operator()(size_t row, size_t col) {
            assert(row >= 0 && row < numRow); // Ensure row is within bounds
            assert(col >= 0 && col < numCol); // Ensure index is within bounds
            return data[row][col];
        }

        const T& operator()(size_t row, size_t col) const {
            assert(row >= 0 && row < numRow); // Ensure row is within bounds
            assert(col >= 0 && col < numCol); // Ensure index is within bounds
            return data[row][col];
        }

        Matrix operator+(const Matrix& other) const {
            assert(numRow == other.numRow && numCol == other.numCol); // Ensure dimensions match
            Matrix result(numRow, numCol);
            for (size_t i = 0; i < numRow; ++i) {
                for (size_t j = 0; j < numCol; ++j) {
                    result(i, j) = (*this)(i, j) + other(i, j); // (*this) dereference the pointer turning it to an object
                }
            }
            return result;
        }

        size_t getNumRow() const {
            return numRow;
        }
        size_t getNumCol() const {
            return numCol;
        }
        double FrobeniusNorm() const {
            double sum = 0.0;
            for (size_t i = 0; i < numRow; ++i) {
                for (size_t j = 0; j < numCol; ++j) {
                    sum += static_cast<double>((*this)(i,j)) * static_cast<double>((*this)(i,j));
                }
            }
            return sqrt(sum); // Return the square root of the sum of squares
        }
        double RowSumNorm() const {
            double maxSum = 0.0;
            for (size_t i = 0; i < numRow; ++i) {
                double rowSum = 0.0;
                for (size_t j = 0; j < numCol; ++j) {
                    rowSum += std::abs(static_cast<double>((*this)(i, j)));
                }
                std::cout << "- Sum of Row " << i << ": " << rowSum << std::endl; // Debug
                if (rowSum > maxSum) {
                    maxSum = rowSum;
                }
            }
            return maxSum;
        }
        double TotalNorm() const {
            double maxVal = 0.0;
            for (size_t i = 0; i < numRow; ++i) {
                double maxRow = 0.0;
                for (size_t j = 0; j < numCol; ++j) {
                    if(std::abs(static_cast<double>((*this)(i, j))) > maxRow) {
                        maxRow = std::abs(static_cast<double>((*this)(i, j)));
                    }
                }
                if(maxRow > maxVal) {
                    maxVal = maxRow;
                }
            }
            return maxVal * numRow; // Return the maximum absolute value in the matrix multiplied by the number of rows
        }


};

int main() {
    Matrix<int> mat(3, 3); // Create a 3x4 matrix

    for (size_t i = 0; i < mat.getNumRow(); ++i) {
        for (size_t j = 0; j < mat.getNumCol(); ++j) {
            mat(i, j) = i * mat.getNumCol() + j; // Fill the matrix with some values
        }
    }
    // Display the matrix
    for (size_t i = 0; i < mat.getNumRow(); ++i) {
        for (size_t j = 0; j < mat.getNumCol(); ++j) {
            cout << mat(i, j) << " ";
        }
        cout << endl;
    }
    cout << "Frobenius Norm: " << mat.FrobeniusNorm() << endl;
    cout << "Row Sum Norm: " << mat.RowSumNorm() << endl;
    cout << "Total Norm: " << mat.TotalNorm() << endl;

    return 0;

}