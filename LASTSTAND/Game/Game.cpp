#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "GameOver.h"

Game::Game()
{
}

bool Game::Start()
{
    m_player = NewGO<Player>(0, "player");
    m_player->SetName("player");

    m_bg = NewGO<BackGround>(0, "backGround");

    m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

    // 1体目の敵
    m_enemy = NewGO<Enemy>(0, "enemy");

    // 2体目の敵
    m_enemy2 = NewGO<Enemy2>(0, "enemy2");

    return true;
}

Game::~Game()
{
}

void Game::Update()
{
    // すでにゲームオーバー画面が表示されている場合
    if (m_gameOver != nullptr)
    {
        return;
    }

    // プレイヤーがゲームオーバーになったか確認
    if (m_player->IsGameOver())
    {
        // ゲームオーバー画面を生成
        m_gameOver = NewGO<GameOver>(0, "gameOver");
    }
}

void Game::Render(RenderContext& rc)
{
}