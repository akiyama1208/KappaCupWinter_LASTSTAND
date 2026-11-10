#include "stdafx.h"
#include "GameClear.h"

GameClear::GameClear()
{
}

GameClear::~GameClear()
{
}

bool GameClear::Start()
{
    m_spriteRender.Init(
        "Assets/sprite/gameclear.dds",
        1920.0f,
        1080.0f
    );

    return true;
}

void GameClear::Update()
{
    // Aボタンでタイトルに戻る要求
    if (g_pad[0]->IsTrigger(enButtonA))
    {
        m_isRetry = true;
    }
}

void GameClear::Render(RenderContext& rc)
{
    m_spriteRender.Draw(rc);
}