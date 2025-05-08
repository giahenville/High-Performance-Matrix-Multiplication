#include <iostream>
#include <vector>
#include <chrono>

std::vector<std::vector<int> > generateMatrix(int size){

    std::vector<std::vector<int> > matrix;

    for (int i = 0; i < size; i++ ) {
        std::vector<int> arr;
        for ( int j = 0; j < size; j++ ) {
            int num = rand() % (size + 1);
            arr.push_back(num);
        }
        matrix.push_back(arr);
    }

    return matrix;
};


long long timeToExecute(std::vector<std::vector<int> > matrix1, std::vector<std::vector<int> > matrix2){

    auto start = std::chrono::high_resolution_clock::now();
    // Test code
    for ( int i = 0; i < 1000000; i++) {
        int x = i;
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    return duration.count();

};

void printMatrix(const std::vector<std::vector<int> >& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
};

int main(){
    int size = rand() % 10;
    
    std::vector<std::vector<int> > matrix1 = generateMatrix(size);
    std::vector<std::vector<int> > matrix2 = generateMatrix(size);

    std::cout << "Matrix1:\n";
    printMatrix(matrix1);
    std::cout << "Matrix2:\n";
    printMatrix(matrix2);

    long long result = timeToExecute(matrix1, matrix2);

    std::cout << "Time taken to execute: " << result << " microseconds \n";
    // std::cout << "type of result: " << typeid(result).name() << "\n";
    return 0;
}
