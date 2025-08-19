#include <iostream>
#include <vector>
#include <chrono>

using Matrix = std::vector<std::vector<int>>;

Matrix generateMatrix(int size);
long long timeToExecute(Matrix& A, Matrix& B);
Matrix matrixMultiplication(const Matrix& A, const Matrix& B);
void printMatrix(const Matrix& matrix);

int main(){
    srand(time(0)); // seed random once
    int size = (rand() % 5) + 2; // random size between 2 and 6
    
    Matrix matrix1 = generateMatrix(size);
    Matrix matrix2 = generateMatrix(size);

    std::cout << "Matrix1:\n";
    printMatrix(matrix1);
    std::cout << "Matrix2:\n";
    printMatrix(matrix2);

    long long result = timeToExecute(matrix1, matrix2);

    std::cout << "Time taken to execute: " << result << " microseconds \n";
    // std::cout << "type of result: " << typeid(result).name() << "\n";
    return 0;
}

Matrix generateMatrix(int size){

    Matrix matrix;

    for (int i = 0; i < size; i++ ) {
        std::vector<int> arr;
        for ( int j = 0; j < size; j++ ) {
            int num = rand() % 10;
            arr.push_back(num);
        }
        matrix.push_back(arr);
    }

    return matrix;
};


long long timeToExecute(Matrix& A, Matrix& B){

    auto start = std::chrono::high_resolution_clock::now();
    // TODO: run matrix multiplication algorithm here
    
    Matrix res = matrixMultiplication(A, B);
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Result:\n";
    printMatrix(res);
    return duration.count();

};

// Function to multiply two square matrices
Matrix matrixMultiplication(const Matrix& A, const Matrix& B) {
    size_t n = A.size();
    Matrix C(n, std::vector<int>(n, 0));

    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            for (size_t element = 0; element < n; element++) {
                C[row][col] += A[row][element] * B[element][col];
            }
        }
    }
    return C;
}

void printMatrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
};
