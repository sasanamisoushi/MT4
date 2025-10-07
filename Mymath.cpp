#include "Mymath.h"
#include <cmath>

Matrix4x4 Mymath::MakeRotateAxisAngle(const Vector3 &axis, float angle) {
    // 軸を正規化
    Vector3 n = axis;
    float x = n.x;
    float y = n.y;
    float z = n.z;

    float c = std::cos(angle);
    float s = std::sin(angle);
    float t = 1.0f - c;

    Matrix4x4 result{};

    result.m[0][0] = t * x * x + c;
    result.m[0][1] = t * x * y + s * z; 
    result.m[0][2] = t * x * z - s * y;
    result.m[0][3] = 0.0f;

    result.m[1][0] = t * x * y - s * z;
    result.m[1][1] = t * y * y + c;
    result.m[1][2] = t * y * z + s * x;
    result.m[1][3] = 0.0f;

    result.m[2][0] = t * x * z + s * y;
    result.m[2][1] = t * y * z - s * x;
    result.m[2][2] = t * z * z + c;
    result.m[2][3] = 0.0f;

    result.m[3][0] = 0.0f;
    result.m[3][1] = 0.0f;
    result.m[3][2] = 0.0f;
    result.m[3][3] = 1.0f;

    return result;
}



Vector3 Mymath::Normalize(const Vector3 &v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length == 0.0f) {
        return { 0.0f, 0.0f, 0.0f };
    }
    float invLen = 1.0f / length;
    return { v.x * invLen, v.y * invLen, v.z * invLen };
}