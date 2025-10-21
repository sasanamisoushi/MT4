#include <Novice.h>
#include "Mymath.h"

const char kWindowTitle[] = "LE2C_16_sasnami_sousi";

Mymath myMath_;


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
		
		Vector3 from0 = myMath_.Normalize(Vector3{ 1.0f,0.7f,0.5f });
		Vector3 to0 = -from0;
		Vector3 from1 = myMath_.Normalize(Vector3{ -0.6f,0.9f,0.2f });
		Vector3 to1 = myMath_.Normalize(Vector3{ 0.4f,0.7f,-0.5f });
		Matrix4x4 rotateMatrix0 = myMath_.DirectionToDirection(
			myMath_.Normalize(Vector3{ 1.0f,0.0f,0.0f }), myMath_.Normalize(Vector3{ -1.0f,0.0f,0.0f }));

		Matrix4x4 rotateMatrix1 = myMath_.DirectionToDirection(from0, to0);
		Matrix4x4 rotateMatrix2 = myMath_.DirectionToDirection(from1, to1);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 30,rotateMatrix0,"rotateMatrix0");
		MatrixScreenPrintf(0, kRowHeight * 6, rotateMatrix1, "rotateMatrix1");
		MatrixScreenPrintf(0, kRowHeight * 11, rotateMatrix2, "rotateMatrix2");

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
