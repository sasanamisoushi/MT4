#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;

class Mymath {
public:
	Matrix4x4 MakeRotateAxisAngle(const Vector3 &axis, float sngle);


	Vector3 Normalize(const Vector3 &v);
};

