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
		
		Quaternion rotation = quaternionMath_.MakeRotateAxisAngle(myMath_.Normalize(Vector3{ 1.0f,0.4f,-0.2f }), 0.45f);
		Vector3 pointY = { 2.1f,-0.9f,1.3f };
		Matrix4x4 rotateMatrix = quaternionMath_.MakeRotateMatrix(rotation);
		Vector3 rotateByQuaternion = quaternionMath_.RotateVector(pointY, rotation);
		Vector3 rotateByMatrix = myMath_.TransformCoord(pointY, rotateMatrix);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		QuaternionScreenPrintf(0,kRowHeight*1,rotation,"rotation");
		MatrixScreenPrintf(0, kRowHeight * 3, rotateMatrix, " rotateMatrix");
		VectorScreenPrintf(0, kRowHeight * 7, rotateByQuaternion, "rotateByQuaternion");
		VectorScreenPrintf(0, kRowHeight * 8, rotateByMatrix, "rotateByMatrix");
		

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
