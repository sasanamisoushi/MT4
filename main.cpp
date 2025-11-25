#include <Novice.h>
#include "Mymath.h"
#include "QuaternionMath.h"

const char kWindowTitle[] = "LE2C_16_sasnami_sousi";

Mymath myMath_;
QuaternionMath quaternionMath_;

static const int kRowHeight = 30;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4 &matrix, const char *label) {
	Novice::ScreenPrintf(x, y - kRowHeight, "%s", label); // ラベル表示（上に）
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%7.3f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vector3 &vector, const char *label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}



void QuaternionScreenPrintf(int x, int y, const Quaternion &quaternion, const char *label) {
	// ラベルを上に表示
	Novice::ScreenPrintf(x, y - kRowHeight, "%s", label);
	// 各成分を1行で表示
	Novice::ScreenPrintf(x + 0 * kColumnWidth, y, "%7.2f", quaternion.x);
	Novice::ScreenPrintf(x + 1 * kColumnWidth, y, "%7.2f", quaternion.y);
	Novice::ScreenPrintf(x + 2 * kColumnWidth, y, "%7.2f", quaternion.z);
	Novice::ScreenPrintf(x + 3 * kColumnWidth, y, "%7.2f", quaternion.w);
}

void FloatScreenPrintf(int x, int y, float value, const char *label) {
	// ラベルを上に表示
	Novice::ScreenPrintf(x, y - kRowHeight, "%s", label);
	// 値を表示
	Novice::ScreenPrintf(x, y, "%7.2f", value);
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		Quaternion rotation0 = quaternionMath_.MakeRotateAxisAngle({ 0.71f,0.71f,0.0f }, 0.3f);
		Quaternion rotation1 = quaternionMath_.MakeRotateAxisAngle({ 0.71f,0.0f,0.71f }, 3.141592f);

		Quaternion interpolate0 = quaternionMath_.Slerp(rotation0, rotation1, 0.0f);
		Quaternion interpolate1 = quaternionMath_.Slerp(rotation0, rotation1, 0.3f);
		Quaternion interpolate2 = quaternionMath_.Slerp(rotation0, rotation1, 0.5f);
		Quaternion interpolate3 = quaternionMath_.Slerp(rotation0, rotation1, 0.7f);
		Quaternion interpolate4 = quaternionMath_.Slerp(rotation0, rotation1, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		QuaternionScreenPrintf(0, kRowHeight * 2, interpolate0, ": interpolate0, slerp(q0, q1,0.0f)");
		QuaternionScreenPrintf(0, kRowHeight * 4, interpolate1, ": interpolate1, slerp(q0, q1,0.3f)");
		QuaternionScreenPrintf(0, kRowHeight * 6, interpolate2, ": interpolate2, slerp(q0, q1,0.5f)");
		QuaternionScreenPrintf(0, kRowHeight * 8, interpolate3, ": interpolate3, slerp(q0, q1,0.7f)");
		QuaternionScreenPrintf(0, kRowHeight * 10, interpolate4, ": interpolate4, slerp(q0, q1,1.0f)");
		
		

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
