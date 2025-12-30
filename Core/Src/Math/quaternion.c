//
// Created by lukas-wiener on 12/30/25.
//
#include "quaternion.h"

Quaternion4D quaternion4d_multiply(Quaternion4D q1, Quaternion4D q2) {
    Quaternion4D res;
    res.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
    res.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
    res.y = q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x;
    res.z = q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w;
    return res;
}

Quaternion4D quaternion4d_conjugate(Quaternion4D q) {
    Quaternion4D res = {q.w, -q.x, -q.y, -q.z};
    return res;
}