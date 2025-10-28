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
		
		Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
		Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };

		Quaternion identity = quaternionMath_.IdentityQuatenion();
		Quaternion conj = quaternionMath_.Conjugate(q1);
		Quaternion inv = quaternionMath_.Inverse(q1);
		Quaternion normal = quaternionMath_.Normalize(q1);
		Quaternion mul1 = quaternionMath_.Multiply(q1, q2);
		Quaternion mul2 = quaternionMath_.Multiply(q2, q1);
		float norm = quaternionMath_.Norm(q1);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		QuaternionScreenPrintf(10, 30, identity, "identity");
		QuaternionScreenPrintf(10, 80, conj, "Conjugate");
		QuaternionScreenPrintf(10, 140, inv, "Inverse");
		QuaternionScreenPrintf(10, 190, normal, "Normalize");
		QuaternionScreenPrintf(10, 240, mul1, "Multiply(q1, q2)");
		QuaternionScreenPrintf(10, 290, mul2, "Multiply(q2, q1)");
		FloatScreenPrintf(10, 340, norm, "Norm");

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
