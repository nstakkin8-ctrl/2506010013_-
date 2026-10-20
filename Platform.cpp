
#include "Platform.h"

Platform::Platform(
    float x,
    float z,
    float topY,
    float w,
    float d
)
{
    position = VGet(x, topY, z);
    width = w;
    depth = d;
    height = 30.0f;
}

void Platform::Draw() const
{
    VECTOR minPos = VGet(
        position.x - width / 2.0f,
        position.y - height,
        position.z - depth / 2.0f
    );

    VECTOR maxPos = VGet(
        position.x + width / 2.0f,
        position.y,
        position.z + depth / 2.0f
    );

    DrawCube3D(
        minPos,
        maxPos,
        GetColor(70, 170, 100),
        GetColor(70, 170, 100),
        TRUE
    );
}

float Platform::GetLeft() const
{
    return position.x - width / 2.0f;
}

float Platform::GetRight() const
{
    return position.x + width / 2.0f;
}

float Platform::GetFront() const
{
    return position.z - depth / 2.0f;
}

float Platform::GetBack() const
{
    return position.z + depth / 2.0f;
}

float Platform::GetTop() const
{
    return position.y;
}
