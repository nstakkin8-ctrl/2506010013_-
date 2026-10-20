
#include "Camera.h"
#include <cmath>

namespace
{
    constexpr float MOUSE_SENSITIVITY = 0.0009f;
    constexpr float MIN_PITCH = -0.7f;
    constexpr float MAX_PITCH = 0.7f;
}

Camera::Camera()
{
    yaw = 0.0f;
    pitch = 0.2f;
    distance = 450.0f;

    screenWidth = 1280;
    screenHeight = 720;
}

void Camera::Initialize()
{
    yaw = 0.0f;
    pitch = 0.2f;
    distance = 450.0f;

    GetScreenState(
        &screenWidth,
        &screenHeight,
        nullptr
    );

    // マウスカーソルを非表示にする
    SetMouseDispFlag(FALSE);

    // マウスを画面中央に移動
    SetMousePoint(
        screenWidth / 2,
        screenHeight / 2
    );
}

void Camera::Update(VECTOR target)
{
    int mouseX, mouseY;

    // 現在のマウス位置を取得
    GetMousePoint(&mouseX, &mouseY);

    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    // 画面中央からの移動量
    int mouseDX = mouseX - centerX;
    int mouseDY = mouseY - centerY;

    // マウスの移動量だけカメラの角度を変更
    yaw += mouseDX * MOUSE_SENSITIVITY;
    pitch -= mouseDY * MOUSE_SENSITIVITY;

    // 上下を向きすぎないように制限
    if (pitch < MIN_PITCH)
        pitch = MIN_PITCH;

    if (pitch > MAX_PITCH)
        pitch = MAX_PITCH;

    // マウスを中央に戻して、続けて視点を動かせるようにする
    SetMousePoint(centerX, centerY);

    // カメラの位置を計算
    float horizontalDistance =
        distance * cosf(pitch);

    VECTOR cameraPos = VGet(
        target.x + sinf(yaw) * horizontalDistance,
        target.y + 40.0f + sinf(pitch) * distance,
        target.z - cosf(yaw) * horizontalDistance
    );

    // プレイヤーの上半身を見る
    VECTOR cameraTarget = VGet(
        target.x,
        target.y + 40.0f,
        target.z
    );

    SetCameraPositionAndTarget_UpVecY(
        cameraPos,
        cameraTarget
    );
}
