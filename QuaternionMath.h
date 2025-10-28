#pragma once

struct Quaternion {
    float x;
    float y;
    float z;
    float w;

   
};

struct QuaternionMath {
public:
    //積
    Quaternion Multiply(const Quaternion &lhs, const Quaternion &rhs);

    //単位Quaternion
    Quaternion IdentityQuatenion();

    //共役Quaternion
    Quaternion Conjugate(const Quaternion &quaternion);

    // Quaternionのnormを返す
    float Norm(const Quaternion &quaternion);

    //正規化
    Quaternion Normalize(const  Quaternion &quaternion);

    //逆Quaternion
    Quaternion Inverse(const Quaternion &quaternion);
};