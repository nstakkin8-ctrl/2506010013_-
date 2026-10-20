
#include "Player.h"

namespace
{
    constexpr float MOVE_SPEED = 300.0f;
    constexpr float JUMP_POWER = 650.0f;
    constexpr float GRAVITY = 1000.0f;
    constexpr float DT = 1.0f / 60.0f;
}

Player::Player()
{
    Initialize();
}

void Player::Initialize()
{
    position = VGet(0, 40, -150);

    velocityY = 0.0f;
    previousFeetY = 0.0f;

    onGround = true;
    previousJumpKey = 0;

    halfX = 30.0f;
    halfY = 40.0f;
    halfZ = 30.0f;
}

void Player::Update()
{
    // 物理計算前の足元の高さを記録
    previousFeetY = position.y - halfY;

    // 移動
    if (CheckHitKey(KEY_INPUT_A))
        position.x -= MOVE_SPEED * DT;

    if (CheckHitKey(KEY_INPUT_D))
        position.x += MOVE_SPEED * DT;

    if (CheckHitKey(KEY_INPUT_W))
        position.z += MOVE_SPEED * DT;

    if (CheckHitKey(KEY_INPUT_S))
        position.z -= MOVE_SPEED * DT;

    // ジャンプキーを押した瞬間だけジャンプ
    int jumpKey = CheckHitKey(KEY_INPUT_SPACE);

    if (jumpKey && !previousJumpKey && onGround)
    {
        velocityY = JUMP_POWER;
        onGround = false;
    }

    previousJumpKey = jumpKey;

    // 重力と上下移動
    if (!onGround)
    {
        velocityY -= GRAVITY * DT;
        position.y += velocityY * DT;
    }
}

void Player::Draw()
{
    // キャラクターの中心位置
    float x = position.x;
    float y = position.y;
    float z = position.z;

    int skinColor = GetColor(255, 200, 150);
    int shirtColor = GetColor(40, 120, 255);
    int pantsColor = GetColor(50, 60, 100);
    int shoeColor = GetColor(40, 40, 40);

    // 頭
    DrawCube3D(
        VGet(x - 15, y + 15, z - 15),
        VGet(x + 15, y + 45, z + 15),
        skinColor, skinColor, TRUE);

    // 胴体
    DrawCube3D(
        VGet(x - 17, y - 12, z - 10),
        VGet(x + 17, y + 15, z + 10),
        shirtColor, shirtColor, TRUE);

    // 左腕
    DrawCube3D(
        VGet(x - 27, y - 12, z - 8),
        VGet(x - 17, y + 12, z + 8),
        skinColor, skinColor, TRUE);

    // 右腕
    DrawCube3D(
        VGet(x + 17, y - 12, z - 8),
        VGet(x + 27, y + 12, z + 8),
        skinColor, skinColor, TRUE);

    // 左脚
    DrawCube3D(
        VGet(x - 15, y - 38, z - 9),
        VGet(x - 2, y - 12, z + 9),
        pantsColor, pantsColor, TRUE);

    // 右脚
    DrawCube3D(
        VGet(x + 2, y - 38, z - 9),
        VGet(x + 15, y - 12, z + 9),
        pantsColor, pantsColor, TRUE);

    // 靴
    DrawCube3D(
        VGet(x - 16, y - 40, z - 11),
        VGet(x - 1, y - 35, z + 11),
        shoeColor, shoeColor, TRUE);

    DrawCube3D(
        VGet(x + 1, y - 40, z - 11),
        VGet(x + 16, y - 35, z + 11),
        shoeColor, shoeColor, TRUE);
}

VECTOR Player::GetPosition() const
{
    return position;
}

float Player::GetFeetY() const
{
    return position.y - halfY;
}

float Player::GetPreviousFeetY() const
{
    return previousFeetY;
}

float Player::GetVelocityY() const
{
    return velocityY;
}

bool Player::IsOnGround() const
{
    return onGround;
}

void Player::SetPosition(VECTOR pos)
{
    position = pos;
}

void Player::SetVelocityY(float velocity)
{
    velocityY = velocity;
}

void Player::SetOnGround(bool grounded)
{
    onGround = grounded;
}

float Player::GetHalfX() const { return halfX; }
float Player::GetHalfY() const { return halfY; }
float Player::GetHalfZ() const { return halfZ; }
