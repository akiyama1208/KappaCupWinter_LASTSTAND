#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

bool GameOver::Start()
{
    m_spriteRender.Init(
        "Assets/sprite/gameover.dds",
        1920.0f,
        1080.0f
    );

    return true;
}

void GameOver::Update()
{
    // Aボタンでリトライ要求
    if (g_pad[0]->IsTrigger(enButtonA))
    {
        m_isRetry = true;
    }
}

void GameOver::Render(RenderContext& rc)
{
    m_spriteRender.Draw(rc);
}