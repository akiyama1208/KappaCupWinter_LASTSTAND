#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "EnemyBulletPool.h"
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

    // 敵弾プールを生成
    NewGO<EnemyBulletPool>(0, "enemyBulletPool");

    // 1体目の敵だけ生成
    m_enemy = NewGO<Enemy>(0, "enemy");

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
        m_gameOver = NewGO<GameOver>(0, "gameOver");
        return;
    }

    // Enemy1が倒されたらEnemy2を生成
    if (m_enemy == nullptr && !m_isEnemy2Spawned)
    {
        m_enemy2 = NewGO<Enemy2>(0, "enemy2");
        m_isEnemy2Spawned = true;
    }

    // Enemy1が削除されたか確認
    if (m_enemy != nullptr)
    {
        if (FindGO<Enemy>("enemy") == nullptr)
        {
            m_enemy = nullptr;
        }
    }
}

void Game::Render(RenderContext& rc)
{
}