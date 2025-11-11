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

Quaternion QuaternionMath::MakeRotateAxisAngle(const Vector3 &axis, float angle) {  
  // 軸を正規化  
  Vector3 n = Mymath::Normalize(axis);  

  // 回転角の半分を使う（クォータニオンの特徴）  
  float halfAngle = angle * 0.5f;  
  float sinHalf = std::sin(halfAngle);  
  float cosHalf = std::cos(halfAngle);  

  // クォータニオンを作成  
  Quaternion q;  
  q.x = n.x * sinHalf;  
  q.y = n.y * sinHalf;  
  q.z = n.z * sinHalf;  
  q.w = cosHalf;  

  return q;  
}

Vector3 QuaternionMath::RotateVector(const Vector3 &v, const Quaternion &quaternion) {
    // クォータニオンを正規化しておく（安全のため）
    Quaternion normQ = Normalize(quaternion);

    // q の共役（逆回転）
    Quaternion conjQ;
    conjQ.x = -normQ.x;
    conjQ.y = -normQ.y;
    conjQ.z = -normQ.z;
    conjQ.w = normQ.w;

    // v をクォータニオンに変換（純虚クォータニオン）
    Quaternion vecQ;
    vecQ.x = v.x;
    vecQ.y = v.y;
    vecQ.z = v.z;
    vecQ.w = 0.0f;

    // 回転: q * v * q⁻¹
    Quaternion resultQ = Multiply(Multiply(normQ, vecQ), conjQ);

    // 結果のベクトル部分を返す
    return { resultQ.x, resultQ.y, resultQ.z };
}

Matrix4x4 QuaternionMath::MakeRotateMatrix(const Quaternion &quaternion) {
    // クォータニオンを正規化（安全のため）
    Quaternion normQ = Normalize(quaternion);
    float x = normQ.x;
    float y = normQ.y;
    float z = normQ.z;
    float w = normQ.w;

    // 3x3の回転成分を求める
    Matrix4x4 m;

    m.m[0][0] = 1.0f - 2.0f * (y * y + z * z);
    m.m[0][1] = 2.0f * (x * y + z * w);
    m.m[0][2] = 2.0f * (x * z - y * w);
    m.m[0][3] = 0.0f;

    m.m[1][0] = 2.0f * (x * y - z * w);
    m.m[1][1] = 1.0f - 2.0f * (x * x + z * z);
    m.m[1][2] = 2.0f * (y * z + x * w);
    m.m[1][3] = 0.0f;

    m.m[2][0] = 2.0f * (x * z + y * w);
    m.m[2][1] = 2.0f * (y * z - x * w);
    m.m[2][2] = 1.0f - 2.0f * (x * x + y * y);
    m.m[2][3] = 0.0f;

    // 平行移動と透視部分は単位行列としておく
    m.m[3][0] = 0.0f;
    m.m[3][1] = 0.0f;
    m.m[3][2] = 0.0f;
    m.m[3][3] = 1.0f;

    return m;
}
