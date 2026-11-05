#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver()
{
    // GAME OVERの表示位置
    m_fontRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
}

GameOver::~GameOver()
{
}

bool GameOver::Start()
{
    // ゲームオーバーの文字を設定
    m_fontRender.SetText(L"GAME OVER");

    // 文字の大きさ
    m_fontRender.SetScale(2.0f);

    return true;
}

void GameOver::Update()
{
}

void GameOver::Render(RenderContext& rc)
{
    m_fontRender.Draw(rc);
}