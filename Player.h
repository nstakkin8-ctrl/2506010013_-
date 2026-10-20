
#pragma once
#include "DxLib.h"

class Player
{
private:
    VECTOR position;

    float velocityY;
    float previousFeetY;

    bool onGround;
    int previousJumpKey;

    float halfX;
    float halfY;
    float halfZ;

public:
    Player();

    void Initialize();
    void Update();
    void Draw();

    VECTOR GetPosition() const;
    float GetFeetY() const;
    float GetPreviousFeetY() const;
    float GetVelocityY() const;

    bool IsOnGround() const;

    void SetPosition(VECTOR pos);
    void SetVelocityY(float velocity);
    void SetOnGround(bool grounded);

    float GetHalfX() const;
    float GetHalfY() const;
    float GetHalfZ() const;
};
