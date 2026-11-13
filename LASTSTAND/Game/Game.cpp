#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "EnemyBulletPool.h"
#include "Aim.h"
#include "Title.h"
#include "GameClear.h"
#include "GameOver.h"
#include "sound/SoundEngine.h"

Game::Game()
{
}

Game::~Game()
{
    // プレイヤー弾を削除
    std::vector<Bullet*> bullets = FindGOs<Bullet>("bullet");

    for (Bullet* bullet : bullets)
    {
        DeleteGO(bullet);
    }

    // 敵弾を削除
    std::vector<EnemyBullet*> enemyBullets =
        FindGOs<EnemyBullet>("enemyBullet");

    for (EnemyBullet* bullet : enemyBullets)
    {
        DeleteGO(bullet);
    }

    // 敵弾プールを削除
    EnemyBulletPool* enemyBulletPool =
        FindGO<EnemyBulletPool>("enemyBulletPool");

    DeleteGO(enemyBulletPool);

    // 敵を削除
    Enemy* enemy = FindGO<Enemy>("enemy");
    DeleteGO(enemy);

    Enemy2* enemy2 = FindGO<Enemy2>("enemy2");
    DeleteGO(enemy2);

    // プレイヤーを削除
    DeleteGO(m_player);

    // カメラを削除
    DeleteGO(m_gameCamera);

    // 背景を削除
    DeleteGO(m_bg);

    // ゲームオーバー画面を削除
    DeleteGO(m_gameOver);

    // ゲームクリア画面を削除
    DeleteGO(m_gameClear);
}

bool Game::Start()
{
    // 命中SEを読み込む
    g_soundEngine->ResistWaveFileBank(
        3, "Assets/sound/hit.wav");

    // 敵の発射SEを読み込む
    g_soundEngine->ResistWaveFileBank(
        4, "Assets/sound/enemy_shoot.wav");
    
    // プレイヤー被弾SEを読み込む
    g_soundEngine->ResistWaveFileBank(
        5, "Assets/sound/damage.wav");

    // 敵撃破SEを読み込む
    g_soundEngine->ResistWaveFileBank(
        6, "Assets/sound/enemy_dead.wav");
    
    NewGO<Aim>(0, "aim");

    // プレイヤー生成
    m_player = NewGO<Player>(0, "player");
    m_player->SetName("player");

    // 背景生成
    m_bg = NewGO<BackGround>(0, "backGround");

    // カメラ生成
    m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

    // 敵弾プール生成
    NewGO<EnemyBulletPool>(0, "enemyBulletPool");

    // 1体目の敵生成
    m_enemy = NewGO<Enemy>(0, "enemy");

    return true;
}

void Game::Update()
{
    // GAME OVER画面でAボタンが押されたか確認
    if (m_gameOver != nullptr && m_gameOver->IsRetry())
    {
        // タイトル画面を生成
        NewGO<Title>(0, "title");

        // Gameを削除
        DeleteGO(this);
        return;
    }

    // GAME CLEAR画面でAボタンが押されたか確認
    if (m_gameClear != nullptr && m_gameClear->IsRetry())
    {
        // タイトル画面を生成
        NewGO<Title>(0, "title");

        // Gameを削除
        DeleteGO(this);
        return;
    }

    // ゲームオーバー後は停止
    if (m_gameOver != nullptr)
    {
        return;
    }

    // ゲームクリア後は停止
    if (m_gameClear != nullptr)
    {
        return;
    }

    // プレイヤーがゲームオーバーになったか確認
    if (m_player->IsGameOver())
    {
        m_gameCamera->SetCameraActive(false);
        ShowCursor(TRUE);
        m_gameOver = NewGO<GameOver>(0, "gameOver");
        return;
    }

    // Enemy1が削除されたか確認
    if (m_enemy != nullptr)
    {
        if (FindGO<Enemy>("enemy") == nullptr)
        {
            m_enemy = nullptr;
        }
    }

    // Enemy1が倒されたらEnemy2を生成
    if (m_enemy == nullptr && !m_isEnemy2Spawned)
    {
        OutputDebugStringA("Enemy2 Spawn Start\n");

        m_enemy2 = NewGO<Enemy2>(0, "enemy2");
        m_isEnemy2Spawned = true;

        OutputDebugStringA("Enemy2 Spawn End\n");
    }

    // Enemy2が削除されたか確認
    if (m_isEnemy2Spawned && m_enemy2 != nullptr)
    {
        if (FindGO<Enemy2>("enemy2") == nullptr)
        {
            m_enemy2 = nullptr;
        }
    }

    // Enemy1・Enemy2を倒したらゲームクリア
    if (m_isEnemy2Spawned && m_enemy2 == nullptr)
    {
        m_gameCamera->SetCameraActive(false);
        ShowCursor(TRUE);
        m_gameClear = NewGO<GameClear>(0, "gameClear");
        return;
    }
}

void Game::Render(RenderContext& rc)
{
}