#define NOMINMAX
#include <Windows.h>
#include "QuaternionMath.h"  
#include <cmath>
#include <algorithm>
 


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

Quaternion QuaternionMath::Slerp(const Quaternion &q0, const Quaternion &q1, float t) {
    // t をクランプ（安全のため）
    if (t <= 0.0f) return q0;
    if (t >= 1.0f) return q1;

    Quaternion q0n = Normalize(q0);
    Quaternion q1n = Normalize(q1);

    float cosTheta = Dot(q0n, q1n);

    // 最短経路を取るため、内積が負なら q1 を反転する
    if (cosTheta < 0.0f) {
        q1n.x = -q1n.x; q1n.y = -q1n.y; q1n.z = -q1n.z; q1n.w = -q1n.w;
        cosTheta = -cosTheta;
    }

    const float kEpsilon = 1e-6f;
    // 角度が非常に小さい（ほぼ同じ向き）場合は線形補間して正規化（数値安定化）
    if (cosTheta > 1.0f - 1e-6f) {
        // LERP: q = (1-t)*q0 + t*q1
        Quaternion result = {
            q0.x + t * (q1.x - q0.x),
            q0.y + t * (q1.y - q0.y),
            q0.z + t * (q1.z - q0.z),
            q0.w + t * (q1.w - q0.w)
        };
        return Normalize(result);
    } else {
        // 通常のSLERP
        float theta = std::acos(std::min(std::max(cosTheta, -1.0f), 1.0f)); // 角度
        float sinTheta = std::sin(theta);

        // 安全対策（ゼロ除算回避）
        if (std::fabs(sinTheta) < kEpsilon) {
            // sinTheta が小さいならLERPにフォールバック
            Quaternion result = {
                q0.x + t * (q1.x - q0.x),
                q0.y + t * (q1.y - q0.y),
                q0.z + t * (q1.z - q0.z),
                q0.w + t * (q1.w - q0.w)
            };
            return Normalize(result);
        }

        float a = std::sin((1.0f - t) * theta) / sinTheta;
        float b = std::sin(t * theta) / sinTheta;

        Quaternion result = {
            a * q0.x + b * q1.x,
            a * q0.y + b * q1.y,
            a * q0.z + b * q1.z,
            a * q0.w + b * q1.w
        };

        return Normalize(result);
    }
}

float QuaternionMath::Dot(const Quaternion &q1, const Quaternion &q2) {
    return q1.x * q2.x +q1.y * q2.y +q1.z * q2.z +q1.w * q2.w;
}
