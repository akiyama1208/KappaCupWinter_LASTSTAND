#include "stdafx.h"
#include "Enemy2.h"
#include "Player.h"
#include "EnemyBulletPool.h"
#include "sound/SoundSource.h"

bool Enemy2::Start()
{
    OutputDebugStringA("Enemy2 Start Begin\n");

    // HP
    m_hp = 150;
    m_maxHp = 150;

    // 敵2のHP表示位置
    m_hpFontPosition = Vector3(-250.0f, 500.0f, 0.0f);

    // HP表示名
    m_hpLabel = L"ENEMY2 HP";

    // HPバーの背景
    m_hpBarBackRender.Init("Assets/sprite/white.dds", 200.0f, 15.0f);
    m_hpBarBackRender.SetPivot(Vector2(0.0f, 0.5f));
    m_hpBarBackRender.SetPosition(Vector3(-30.0f, 480.0f, 0.0f));
    m_hpBarBackRender.SetMulColor(Vector4(0.3f, 0.3f, 0.3f, 1.0f));

    // HPバー本体
    m_hpBarRender.Init("Assets/sprite/white.dds", 200.0f, 15.0f);
    m_hpBarRender.SetPivot(Vector2(0.0f, 0.5f));
    m_hpBarRender.SetPosition(Vector3(-30.0f, 480.0f, 0.0f));
    m_hpBarRender.SetMulColor(Vector4(0.0f, 1.0f, 0.0f, 1.0f));

    // 初期位置
    m_position = Vector3(4000.0f, 0.0f, 500.0f);
    m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);

    // プレイヤーを取得
    m_player = FindGO<Player>("player");

    // 敵弾プールを取得
    m_enemyBulletPool = FindGO<EnemyBulletPool>("enemyBulletPool");

    // モデルを読み込む
    m_modelRender.Init("Assets/modelData/enemy2/enemy2.tkm");
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();

    // 当たり判定
    m_characterController.Init(125.0f, 200.0f, m_position);

    OutputDebugStringA("Enemy2 Start End\n");

    return true;
}

void Enemy2::Update()
{
    if (m_player == nullptr)
    {
        return;
    }

    if (m_player->IsGameOver())
    {
        return;
    }

    Move();
    Attack();

    m_position = m_characterController.Execute(
        m_moveSpeed,
        1.0f / 60.0f
    );

    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();

    // HPバーの長さを更新
    float hpRate = (float)m_hp / m_maxHp;

    m_hpBarRender.SetScale(
        Vector3(hpRate, 1.0f, 1.0f)
    );

    // HP残量に応じて色を変更
    if (hpRate > 0.5f)
    {
        m_hpBarRender.SetMulColor(Vector4(0.0f, 1.0f, 0.0f, 1.0f));
    }
    else if (hpRate > 0.25f)
    {
        m_hpBarRender.SetMulColor(Vector4(1.0f, 1.0f, 0.0f, 1.0f));
    }
    else if (hpRate > 0.0f)
    {
        m_hpBarRender.SetMulColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
    }

    m_hpBarBackRender.Update();
    m_hpBarRender.Update();
}

void Enemy2::Move()
{
    // プレイヤーとの方向を計算
    Vector3 direction = m_player->position - m_position;
    direction.y = 0.0f;

    float distance = direction.Length();

    if (distance < 1500.0f)
    {
        // 近すぎる場合は後退
        direction.Normalize();
        m_moveSpeed = direction * -m_moveSpeedValue;
    }
    else
    {
        // 遠い場合は停止
        m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);
    }
}

void Enemy2::Attack()
{
    // 敵弾プールがなければ攻撃しない
    if (m_enemyBulletPool == nullptr)
    {
        return;
    }

    const float deltaTime = 1.0f / 60.0f;

    // 攻撃タイマー
    m_attackTimer += deltaTime;

    if (m_attackTimer < m_attackInterval)
    {
        return;
    }

    // タイマーをリセット
    m_attackTimer = 0.0f;

    // 弾の発射位置
    Vector3 bulletPosition = m_position;
    bulletPosition.y += 100.0f;

    // 発射位置からプレイヤーへの方向
    Vector3 direction = m_player->position - bulletPosition;
    direction.Normalize();

    // 敵弾を発射
    m_enemyBulletPool->Shoot(
        bulletPosition,
        direction
    );

    // 発射SEを再生
    SoundSource* se = NewGO<SoundSource>(0);
    se->Init(4);
    se->SetVolume(3.5f);
    se->Play(false);
}