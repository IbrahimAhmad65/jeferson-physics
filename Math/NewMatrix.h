//
// Created by ibrahim on 12/31/22.
//

#ifndef PHYS2_NEWMATRIX_H
#define PHYS2_NEWMATRIX_H


class NewMatrix {
public:
    NewMatrix(double* data, int row, int col);
    NewMatrix(int row, int col);
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


#endif //PHYS2_NEWMATRIX_H
