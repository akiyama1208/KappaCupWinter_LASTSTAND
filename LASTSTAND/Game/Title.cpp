#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title()
{
    spriteRender.Init("Assets/sprite/title2.dds", 1920.0f, 1080.0f);

    // タイトルBGM
    // g_soundEngine->ResistWaveFileBank(0, "Assets/sound/titlebgm.wav");
    // titleBGM = NewGO<SoundSource>(0);
    // titleBGM->Init(0);
    // titleBGM->Play(true);
}

bool Title::Start()
{
    return true;
}

Title::~Title()
{
    // タイトルBGM削除
    DeleteGO(titleBGM);
}

void Title::Update()
{
    // Aボタンでゲーム開始
    if (g_pad[0]->IsTrigger(enButtonA))
    {
        NewGO<Game>(0, "game");
        DeleteGO(this);
        return;
    }
}

void Title::Render(RenderContext& rc)
{
    spriteRender.Draw(rc);
}

