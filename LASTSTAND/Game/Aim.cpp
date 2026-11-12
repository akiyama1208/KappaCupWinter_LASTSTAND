#include "stdafx.h"
#include "Aim.h"

Aim::Aim()
{
}

Aim::~Aim()
{
}

bool Aim::Start()
{
    // 照準画像を読み込む
    m_aimSprite.Init("Assets/sprite/aim.dds",64.0f,64.0f);

    // 画面中央に配置
    m_aimSprite.SetPosition(Vector3(0.0f, 0.0f, 0.0f));

    return true;
}

void Aim::Render(RenderContext& rc)
{
    // 非表示なら描画しない
    if (!m_isVisible)
    {
        return;
    }

    // 照準を描画
    m_aimSprite.Draw(rc);
}