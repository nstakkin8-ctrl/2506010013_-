
#pragma once

#include "Player.h"
#include "Platform.h"
#include "Camera.h"
#include <vector>

class Game
{
private:
    Player player;
    Camera camera;
    std::vector<Platform> platforms;

    bool gameClear;

    void CreatePlatforms();
    void UpdatePlayer();
    void CheckLanding();
    void DrawWorld();

public:
    Game();

    void Initialize();
    void Update();
    void Draw();
};
