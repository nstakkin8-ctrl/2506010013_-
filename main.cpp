
#include "DxLib.h"
#include "Game.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(1280, 720, 32);

    if (DxLib_Init() == -1)
        return -1;

    SetDrawScreen(DX_SCREEN_BACK);
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    SetBackgroundColor(135, 206, 235);

    Game game;
    game.Initialize();

    while (ProcessMessage() == 0 &&
        CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        game.Update();
        game.Draw();
    }

    DxLib_End();

    return 0;
}

