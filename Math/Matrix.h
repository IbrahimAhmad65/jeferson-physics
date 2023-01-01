//
// Created by ibrahim on 12/31/22.
//

#ifndef PHYS2_MATRIX_H
#define PHYS2_MATRIX_H


class Matrix {
private:

    double ** data;
    int row;
    int col;
public:
    int getRow();
    int getCol();
    Matrix(double** data, int row, int col);
    Matrix T();

    void setData(double **data);

    double **getData();

    void fill(double value);


    void fill(double *value);

    Matrix multiply(Matrix in);

    Matrix add(Matrix in);

    void subtract(Matrix in);

    Matrix scale(double scalar);


    int getMaxRank();

    Matrix clone();

    int getRank();

    Matrix reducedRowEchelon();

    void setRow(int row, double *rowData);
};


#endif //PHYS2_MATRIX_H
