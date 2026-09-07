#include "Stage.h"

Stage::Stage()
{
    // 初期値
    modelHandle = -1;

    position = VGet(0.0f, 0.0f, 0.0f);
}

Stage::~Stage()
{
    // モデルが読み込まれていたら削除
    if (modelHandle != -1)
    {
        MV1DeleteModel(modelHandle);
    }
}

bool Stage::Load()
{
    // 3Dモデルを読み込む
    modelHandle = MV1LoadModel("Stage/Stage01.mv1");

    // 読み込み失敗
    if (modelHandle == -1)
    {
        return false;
    }

    // モデルの位置を設定
    MV1SetPosition(modelHandle, position);

    return true;
}

void Stage::SetPosition(VECTOR pos)
{
    position = pos;