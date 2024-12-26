#include<iostream>
#include <fstream>
#include <sstream>
using namespace std;

bool readMatrix(const char* filename, int** &matrix, int &rows, int &cols){
    fstream inFile;
    inFile.open(filename, ios::in);
    if (!inFile) return false;
    
    rows = cols = 0;
    string line;
    while (getline(inFile, line)){
        rows += 1;
        if (rows == 1) {
            istringstream iss(line);
            int num; 
            while(iss >> num) cols += 1;
        }
    }
    if (rows == 0 || cols == 0) return false;
    // cout << rows << " " << cols << "\n";

    matrix = new int* [rows];
    for (int i = 0; i < rows; i++) matrix[i] = new int [cols];
    inFile.clear();
    inFile.seekg(0, ios::beg);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            inFile >> matrix[i][j];
        }
    }
    inFile.close();
    return true;
}

void printMatrix(const char* filename, int **matrix, int rows, int cols){
    fstream outFile;
    outFile.open(filename, ios::out);
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            outFile << matrix[i][j] << " ";
        }
        outFile << "\n";
    }
    outFile.close();
}

bool multiplyMatrices(int **a, int aRows, int aCols, int **b, int bRows, int bCols, int** &res, int &resRows, int &resCols){
    // a(aRows, aCols) * b(bRows, bCols) = res(aRows, bCols); aCols = bRows;
    if (aCols != bRows) return false;
    resRows = aRows; resCols = bCols;
    int m = aCols;
    res = new int* [aRows];
    for (int i = 0; i < resRows; i++){
        res[i] = new int [resCols];
    }
    for (int i = 0; i < resRows; i++){
        for (int j = 0; j < resCols; j++){
            res[i][j] = 0;
            for (int k = 0; k < m; k++){
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return true;
}

void transposeMatrix(int **matrix, int rows, int cols, int** &res, int &resRows, int &resCols){
    resRows = cols; resCols = rows;
    res = new int* [resRows];
    for (int i = 0; i < resRows; i++) res[i] = new int [resCols];

    for (int i = 0; i < resRows; i++) {
        for (int j = 0; j < resCols; j++) {
            res[i][j] = matrix[j][i];
        }
    }
}

int main(){
    int **a = nullptr;
    int **b = nullptr;
    int **c = nullptr;
    int **cT = nullptr;
    int aRows, aCols, bRows, bCols, cRows, cCols, cTRows, cTCols;
    readMatrix("matrix_a.txt", a, aRows, aCols);
    readMatrix("matrix_b.txt", b, bRows, bCols);

    if (multiplyMatrices(a, aRows, aCols, b, bRows, bCols, c, cRows, cCols)) {
        cout << "multiplyMatrices a & b: successful\n";
    } else cout << "multiplyMatrices a & b: failed\n";

    printMatrix("matrix_c.txt", c, cRows, cCols);
    if (readMatrix("matrix_c.txt", c, cRows, cCols)){
        cout << "Print matrix_c: successful\n";
    } else cout << "Print matrix_c: failed\n";
    
    transposeMatrix(c, cRows, cCols, cT, cTRows, cTCols);
    printMatrix("matrix_c_transposed.txt", cT, cTRows, cTCols);
}