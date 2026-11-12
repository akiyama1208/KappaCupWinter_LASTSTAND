#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "HowToPlay.h"

Title::Title()
{
    spriteRender.Init("Assets/sprite/title3.dds", 1920.0f, 1080.0f);

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
    // Aボタンで操作説明画面へ
    if (g_pad[0]->IsTrigger(enButtonA))
    {
        NewGO<HowToPlay>(0, "howToPlay");
        DeleteGO(this);
        return;
    }
}

void Title::Render(RenderContext& rc)
{
    spriteRender.Draw(rc);
}

