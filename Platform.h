#pragma once
#include "DxLib.h"

class Platform
{
private:
    VECTOR position;
    float width;
    float depth;
    float height;

public:
    Platform(
        float x,
        float z,
        float topY,
        float w,
        float d
    );

    void Draw() const;

    float GetLeft() const;
    float GetRight() const;
    float GetFront() const;
    float GetBack() const;
    float GetTop() const;
};

