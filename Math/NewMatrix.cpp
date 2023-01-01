//

#include <valarray>
#include "NewMatrix.h"



//
// Created by ibrahim on 12/31/22.
NewMatrix::NewMatrix(double *data, int row, int col) {
    this->rowSize = row;
    this->colSize = col;
    this->data = data;
}

NewMatrix::NewMatrix(int row, int col) {
    this->rowSize = row;
    this->colSize = col;
    data = new double [row*col];
}

double *NewMatrix::solve(double *right) {
    int N = getRowSize();
    for (int k = 0; k < N; k++) {
        int max = k;
        for (int i = k + 1; i < N; i++) {
            if (std::abs(get(max, k)) < std::abs(get(i, k))) {
                max = i;
            }
        }
        double *temp = getRow(k);
        setRow(k, getRow(max));
        setRow(max, temp);
        double t = right[k];
        right[k] = right[max];
        right[max] = t;
        for (int i = k + 1; i < N; i++) {
            double factor = get(i, k) / get(k, k);
            right[i] -= factor * right[k];
            for (int j = k; j < N; j++) {
                set(i,j,get(i,j)- factor * get(k,j));
            }
        }
    }
    auto *solution = new double[N];
    for (int i = N - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < N; j++) {
            sum += get(i, j) * solution[j];
        }
        solution[i] = (right[i] - sum) / get(i, i);
    }
    return solution;
}

int NewMatrix::getRowSize() const {
    return rowSize;
}

int NewMatrix::getColSize() const {
    return colSize;
}

double NewMatrix::get(int row, int col) {
    return data[row * colSize + col];
}

double *NewMatrix::getRow(int row) {
    auto *out = new double[colSize];
    for (int i = 0; i < colSize; ++i) {
        out[i] = data[row * colSize + i];
    }
    return out;
}


void * NewMatrix::setRow(int row, const double *rowData) {
    for (int i = 0; i < colSize; ++i) {
        data[row * colSize + i] = rowData[i];
    }
}

double *NewMatrix::getData() {
    return data;
}

void NewMatrix::set(int row, int col, double num) {
    this->data[row * colSize + col] = num;
}
