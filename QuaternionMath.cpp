#include "QuaternionMath.h"
#include <cmath>

Quaternion QuaternionMath::Multiply(const Quaternion &lhs, const Quaternion &rhs) {
    Quaternion result;
    result.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
    result.y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
    result.z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;
    result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
    return result;
}

Quaternion QuaternionMath::IdentityQuatenion() {
    Quaternion q;
    q.x = 0.0f;
    q.y = 0.0f;
    q.z = 0.0f;
    q.w = 1.0f;
    return q;
}

Quaternion QuaternionMath::Conjugate(const Quaternion &quaternion) {
    Quaternion result;
    result.x = -quaternion.x;
    result.y = -quaternion.y;
    result.z = -quaternion.z;
    result.w = quaternion.w;
    return result;
}

float QuaternionMath::Norm(const Quaternion &quaternion) {
    return std::sqrt(
        quaternion.x * quaternion.x +
        quaternion.y * quaternion.y +
        quaternion.z * quaternion.z +
        quaternion.w * quaternion.w
    );
}

Quaternion QuaternionMath::Normalize(const Quaternion &quaternion) {
    float norm = Norm(quaternion);
    if (norm == 0.0f) {
        // 長さが0なら単位クォータニオンを返す
        return Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
    }

    Quaternion result;
    result.x = quaternion.x / norm;
    result.y = quaternion.y / norm;
    result.z = quaternion.z / norm;
    result.w = quaternion.w / norm;
    return result;
}

Quaternion QuaternionMath::Inverse(const Quaternion &quaternion) {
    float normSq =
        quaternion.x * quaternion.x +
        quaternion.y * quaternion.y +
        quaternion.z * quaternion.z +
        quaternion.w * quaternion.w;

    if (normSq == 0.0f) {
        // 逆数が存在しない場合は単位クォータニオンを返す
        return Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
    }

    Quaternion conjugate = Conjugate(quaternion);
    Quaternion result;
    result.x = conjugate.x / normSq;
    result.y = conjugate.y / normSq;
    result.z = conjugate.z / normSq;
    result.w = conjugate.w / normSq;
    return result;
}
