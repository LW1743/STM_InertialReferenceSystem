//
// Created by lukas-wiener on 12/30/25.
//
#include "vector.h"

#include <math.h>

double vector3d_dotProduct(Vector3D v1, Vector3D v2) {
    return (v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z);
}

double vector3d_length(Vector3D v) {
    return sqrt(vector3d_dotProduct(v, v));
}

Vector3D vector3d_crossProduct(Vector3D v1, Vector3D v2) {
    Vector3D res;
    res.x = v1.y*v2.z - v1.z*v2.y;
    res.y = v1.z*v2.x - v1.x*v2.z;
    res.z = v1.x*v2.y - v1.y*v2.x;
    return res;
}

void vector3d_scale(Vector3D *v, double s) {
    v->x = v->x*s;
    v->y = v->y*s;
    v->z = v->z*s;
}

void vector3d_normalize(Vector3D *v) {
    double vec_length = vector3d_length(*v);
    v->x = v->x / vec_length;
    v->y = v->y / vec_length;
    v->z = v->z / vec_length;

}