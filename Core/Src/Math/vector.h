//
// Created by lukas-wiener on 12/29/25.
//

#ifndef INERTREFSYS_VECTOR3D_H
#define INERTREFSYS_VECTOR3D_H

typedef struct {
    double x, y, z;
} Vector3D;

double vector3d_length(Vector3D v);

double vector3d_dotProduct(Vector3D v1, Vector3D v2);

Vector3D vector3d_crossProduct(Vector3D v1, Vector3D v2);

void vector3d_scale(Vector3D *v, double s);

void vector3d_normalize(Vector3D *v);

#endif //INERTREFSYS_VECTOR3D_H