//
// Created by lukas on 01/01/2026.
//

#ifndef INERTREFSYS_MATRIX_H
#define INERTREFSYS_MATRIX_H

#include "vector.h"
#include "quaternion.h"

typedef struct {
    double x_1, x_2, x_3;
    double y_1, y_2, y_3;
    double z_1, z_2, z_3;
} Matrix3x3;

Matrix3x3 Matrix3x3_product(Matrix3x3 a, Matrix3x3 b);

double Matrix3x3_determinant(Matrix3x3 a, Matrix3x3 b);



#endif //INERTREFSYS_MATRIX_H