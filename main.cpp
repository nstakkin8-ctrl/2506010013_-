#include "DxLib.h"
#include "Stage.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ウィンドウモード
    ChangeWindowMode(TRUE);

    // 画面サイズ
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);

    // DxLib初期化
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    // 裏画面
    SetDrawScreen(DX_SCREEN_BACK);

    // --------------------------------
    // Stageオブジェクトを作成
    // --------------------------------

    Stage stage;

    // ステージ読み込み
    if (!stage.Load())
    {
        DxLib_End();
        return -1;
    }

    // --------------------------------
    // カメラ
    // --------------------------------

    VECTOR cameraPos = VGet(0.0f, 10.0f, 1100.0f);

    VECTOR cameraTarget = VGet(0.0f, 0.0f, 0.0f);

    SetCameraPositionAndTarget_UpVecY(cameraPos, cameraTarget);

    // --------------------------------
    // ゲームループ
    // --------------------------------

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {

        // 画面クリア
        ClearDrawScreen();

        // ステージ描画
        stage.Draw();

        // 裏画面を表画面へ
        ScreenFlip();
    }

    // DxLib終了
    DxLib_End();

    return 0;
}