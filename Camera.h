
#pragma once
#include "DxLib.h"

class Camera
{
private:
    float yaw;
    float pitch;
    float distance;

    int screenWidth;
    int screenHeight;

public:
    Camera();

    void Initialize();
    void Update(VECTOR target);
};
