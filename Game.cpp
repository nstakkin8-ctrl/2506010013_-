
#include "Game.h"
#include "tchar.h"

Game::Game()
{
    gameClear = false;

}

void Game::Initialize()
{
    player.Initialize();
    camera.Initialize();

    gameClear = false;

    CreatePlatforms();
}

void Game::CreatePlatforms()
{
    platforms.clear();

    // 塔の周囲をらせん状に登る足場
    // 引数の順番：(x, z, topY, width, depth)

    platforms.emplace_back(0, -150, 0, 180, 180);
    platforms.emplace_back(150, 0, 140, 180, 180);
    platforms.emplace_back(0, 150, 280, 180, 180);
    platforms.emplace_back(-150, 0, 420, 180, 180);

    platforms.emplace_back(0, -150, 560, 180, 180);
    platforms.emplace_back(150, 0, 700, 180, 180);
    platforms.emplace_back(0, 150, 840, 180, 180);
    platforms.emplace_back(-150, 0, 980, 180, 180);

    // 頂上のゴール足場
    platforms.emplace_back(0, -100, 1120, 240, 240);
}

void Game::UpdatePlayer()
{
    player.Update();
}



void Game::CheckLanding()
{
    VECTOR pos = player.GetPosition();

    float feetY = player.GetFeetY();

    bool supported = false;

    // --------------------------------
    // 1. 立っている足場があるか確認
    // --------------------------------
    if (player.IsOnGround())
    {
        for (int i = 0;
            i < static_cast<int>(platforms.size());
            i++)
        {
            const Platform& p = platforms[i];

            bool insideX =
                pos.x + player.GetHalfX() > p.GetLeft() &&
                pos.x - player.GetHalfX() < p.GetRight();

            bool insideZ =
                pos.z + player.GetHalfZ() > p.GetFront() &&
                pos.z - player.GetHalfZ() < p.GetBack();

            bool onTop =
                insideX &&
                insideZ &&
                feetY >= p.GetTop() - 0.1f &&
                feetY <= p.GetTop() + 0.1f;

            if (onTop)
            {
                supported = true;
                break;
            }
        }

        // 足場から横に出たら空中状態にする
        if (!supported)
        {
            player.SetOnGround(false);
        }
        else
        {
            return;
        }
    }

    // --------------------------------
    // 2. 上昇中は着地しない
    // --------------------------------
    if (player.GetVelocityY() > 0.0f)
    {
        return;
    }

    // --------------------------------
    // 3. 落下中に全足場との衝突を確認
    // --------------------------------
    float previousFeet = player.GetPreviousFeetY();
    float currentFeet = player.GetFeetY();

    for (int i = 0;
        i < static_cast<int>(platforms.size());
        i++)
    {
        const Platform& p = platforms[i];

        bool insideX =
            pos.x + player.GetHalfX() > p.GetLeft() &&
            pos.x - player.GetHalfX() < p.GetRight();

        bool insideZ =
            pos.z + player.GetHalfZ() > p.GetFront() &&
            pos.z - player.GetHalfZ() < p.GetBack();

        bool crossedTop =
            previousFeet >= p.GetTop() &&
            currentFeet <= p.GetTop();

        if (insideX && insideZ && crossedTop)
        {
            pos.y = p.GetTop() + player.GetHalfY();

            player.SetPosition(pos);
            player.SetVelocityY(0.0f);
            player.SetOnGround(true);

            if (i == static_cast<int>(platforms.size()) - 1)
            {
                gameClear = true;
            }

            return;
        }
    }
}


void Game::Update()
{
    UpdatePlayer();
    CheckLanding();

    VECTOR pos = player.GetPosition();

    // 落下時は最初からやり直す
    if (pos.y < -300.0f)
    {
        player.Initialize();
        gameClear = false;
    }

    camera.Update(player.GetPosition());
}

void Game::DrawWorld()
{
    for (int i = 0;
        i < static_cast<int>(platforms.size());
        i++)
    {
        platforms[i].Draw();
    }

    player.Draw();

    // 中央の塔
    DrawCube3D(
        VGet(-60, 0, -60),
        VGet(60, 1150, 60),
        GetColor(110, 115, 130),
        GetColor(65, 70, 85),
        TRUE
    );
}




    void Game::Draw()
    {
        ClearDrawScreen();

        DrawWorld();

        DrawFormatString(
            20, 20,
            GetColor(255, 255, 255),
            _T("WASD: Move"));

        DrawFormatString(
            20, 45,
            GetColor(255, 255, 255),
            _T("SPACE: Jump"));

        DrawFormatString(
            20, 70,
            GetColor(255, 255, 255),
            _T("ESC: Exit"));

        DrawFormatString(
            20, 95,
            GetColor(255, 255, 255),
            _T("Height: %.0f"),
            player.GetPosition().y);

        if (gameClear)
        {
            DrawFormatString(
                500, 300,
                GetColor(255, 255, 0),
                _T("GAME CLEAR!"));
        }

        ScreenFlip();
    }

