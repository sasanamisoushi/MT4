#pragma once
#include "Mymath.h"  

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

    //任意軸回転
	Quaternion MakeRotateAxisAngle(const Vector3& axis, float angle);

	//ベクトルをQuaternionで回転
	Vector3 RotateVector(const Vector3 &v, const Quaternion &quaternion);

	//Quaternionから回転行列を作成
	Matrix4x4 MakeRotateMatrix(const Quaternion &quaternion);
};