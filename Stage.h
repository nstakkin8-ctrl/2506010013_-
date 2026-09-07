#pragma once
#include "DxLib.h"

class Stage
{
private:

    // ステージの3Dモデル
    int modelHandle;

    // ステージの位置
    VECTOR position;

public:

    // コンストラクタ
    Stage();

    // デストラクタ
    ~Stage();

    // ステージを読み込む
    bool Load();

    // ステージの位置を設定
    void SetPosition(VECTOR pos);

    // ステージを描画
    void Draw();
};
