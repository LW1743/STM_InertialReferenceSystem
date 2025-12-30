//
// Created by lukas-wiener on 12/30/25.
//

#ifndef INERTREFSYS_QUATERNION_H
#define INERTREFSYS_QUATERNION_H

typedef struct {
    double x, y, z, w;
} Quaternion4D;

Quaternion4D quaternion4d_multiply(Quaternion4D q1, Quaternion4D q2);

Quaternion4D quaternion4d_conjugate(Quaternion4D q);
#endif //INERTREFSYS_QUATERNION_H