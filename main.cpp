#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>

using Matrix = std::vector<std::vector<int>>;

Matrix generateMatrix(size_t N);
void timeToExecute(Matrix& A, Matrix& B, std::function<Matrix(const Matrix&, const Matrix&)>);
Matrix naiveMMUL(const Matrix& A, const Matrix& B);
void printMatrix(const Matrix& matrix);
Matrix FileToMatrix(std::string_view filepath);

int main(){
    /*
    srand(time(0)); // seed random once
    //int size = (rand() % 5) + 2; // random size between 2 and 6
    int size = 10;
    
    Matrix matrix1 = generateMatrix(size);
    Matrix matrix2 = generateMatrix(size);
    
    std::cout << "Matrix1:\n";
    printMatrix(matrix1);
    std::cout << "Matrix2:\n";
    printMatrix(matrix2);
    */

    // read from external files
    Matrix MatA = FileToMatrix("MatA.txt");
    Matrix MatB = FileToMatrix("MatB.txt");

    std::cout << "C++: naiveMMUL\n";
    timeToExecute(MatA, MatB, naiveMMUL);
    return 0;
}

// Generates an N by N (square) matrix
Matrix generateMatrix(size_t N) {
    Matrix matrix(N, std::vector<int>(N, 0));
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            int num = rand() % 10;
            matrix[i][j] = num;
        }
    }
    return matrix;
};


void timeToExecute(Matrix& A, Matrix& B, std::function<Matrix(const Matrix&, const Matrix&)> mmul) {
    auto start = std::chrono::high_resolution_clock::now();
   
    // function starts running here!
    mmul(A, B);
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "time to execute: " << duration.count() << "\n";
};

// Function to multiply two square matrices using an O(N^3) loop
Matrix naiveMMUL(const Matrix& A, const Matrix& B) {
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

Matrix FileToMatrix(std::string_view filepath) {
    Matrix resultant;

    std::ifstream file(filepath);
    std::string line;

    while (std::getline(file, line)) {
        std::vector<int> tokens;
        std::string token;
        std::stringstream ss(line);

        while (std::getline(ss, token, ' ')) {
            tokens.push_back(stoi(token));
        }

        resultant.push_back(tokens);
    }

    return resultant;
}
