//

#include <iostream>
#include <array>
#include "Matrix.h"


//
// Created by ibrahim on 12/31/22.
Matrix::Matrix(double **data, int row, int col) {
    this->data = data;
    this->col = col;
    this->row = row;
}

Matrix Matrix::T() {
    const int m = row;
    const int n = col;
    auto **transposedMatrix = static_cast<double **>(malloc(sizeof(double) * row * col));;

    if (transposedMatrix != nullptr) {
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                transposedMatrix[x][y] = data[y][x];
            }
        }
    }
    return {(transposedMatrix), col, row};
}



void Matrix::setData(double **data) {
    this->data = data;
}

double **Matrix::getData() {
    return data;
}

//
//Matrix Matrix::multiply(Matrix in) {
//    int i, j, k;
//    int row1 = row;
//    int row2 = in.getRow();
//    int col1 = col;
//    int col2 = in.getCol();
//    if (row1 != col2) {
//        std::cout << "invalid dims" << std::endl;
//    }
//    double out[][] = new double[row1][col2];
//    for (i = 0; i < row1; i++) {
//        for (j = 0; j < col2; j++) {
//            for (k = 0; k < row2; k++)
//                out[i][j] += this.data[i][k] * in.data[k][j];
//        }
//    }
//    return new Matrix(out);
//}
//
//Matrix Matrix::add(Matrix in) {
//    for (int i = 0; i < data.length; i++) {
//        for (int j = 0; j < data[0].length; j++) {
//            data[i][j] += in.data[i][j];
//        }
//    }
//    return clone();
//}
//
//
//void Matrix::subtract(Matrix in) {
//    for (int i = 0; i < data.length; i++) {
//        for (int j = 0; j < data[0].length; j++) {
//            data[i][j] += in.data[i][j];
//        }
//    }
//}
//
//Matrix Matrix::scale(double scalar) {
//    for (int i = 0; i < data.length; i++) {
//        for (int j = 0; j < data[0].length; j++) {
//            data[i][j] *= scalar;
//        }
//    }
//    return clone();
//}


void Matrix::setRow(int row, double *rowData) {
    data[row] = rowData;
}


double *solve(Matrix left, double *right) {
    double **A = left.getData();
    int N = left.getRow();
    for (int k = 0; k < N; k++) {
        int max = k;
        for (int i = k + 1; i < N; i++) {
            if (std::abs(A[i][k]) > std::abs(A[max][k])) { max = i; }
        }
        double *temp = A[k];
        A[k] = A[max];
        A[max] = temp;
        double t = right[k];
        right[k] = right[max];
        right[max] = t;
        for (int i = k + 1; i < N; i++) {
            double factor = A[i][k] / A[k][k];
            right[i] -= factor * right[k];
            for (int j = k; j < N; j++) {
                A[i][j] -= factor * A[k][j];
            }
        }
    }
    auto *solution = new double[N];
    for (int i = N - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < N; j++) {
            sum += A[i][j] * solution[j];
        }
        solution[i] = (right[i] - sum) / A[i][i];
    }
    return solution;
}


Matrix Matrix::clone() {
    return {this->data, row, col};
}

int Matrix::getMaxRank() {
    return row > col ? col : row;
}

int Matrix::getRow() {
    return row;
}

int Matrix::getCol() {
    return col;
}
