#include "stdafx.h"
#include "HowToPlay.h"
#include "Game.h"

bool HowToPlay::Start()
{
    m_spriteRender.Init("Assets/sprite/howtoplay.dds",1920.0f,1080.0f);

    return true;
}

void HowToPlay::Update()
{
    // Aボタンでゲーム開始
    if (g_pad[0]->IsTrigger(enButtonA))
    {
        NewGO<Game>(0, "game");
        DeleteGO(this);
        return;
    }
}

void HowToPlay::Render(RenderContext& rc)
{
    m_spriteRender.Draw(rc);
}