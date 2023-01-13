//
// Created by ibrahim on 12/31/22.
//

#ifndef PHYS2_MATRIX_H
#define PHYS2_MATRIX_H


class Matrix {
public:
    Matrix(double* data, int row, int col);
    Matrix(int row, int col);
    double* getData();
    int getRowSize() const;
    int getColSize() const;
    double get(int row, int col);
    double* solve(double* right);
    double *getRow(int row);
    void * setRow(int row, const double *rowData);
    void set(int row, int col, double data);

private:
    int rowSize;

    int colSize;

    double* data;
};


#endif //PHYS2_MATRIX_H
