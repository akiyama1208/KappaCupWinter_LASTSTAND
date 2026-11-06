#include "stdafx.h"
#include "EnemyBulletPool.h"

EnemyBulletPool::EnemyBulletPool()
{
}

EnemyBulletPool::~EnemyBulletPool()
{
}

// 初期化
bool EnemyBulletPool::Start()
{
    InitBullets();

    return true;
}

// 敵弾を最初に30発生成
void EnemyBulletPool::InitBullets()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        m_bullets[i] = NewGO<EnemyBullet>(0, "enemyBullet");

        // 最初に1回だけ初期化
        m_bullets[i]->Init(
            Vector3(0.0f, -10000.0f, 0.0f),
            Vector3(0.0f, 0.0f, 1.0f)
        );
    }
}

// 敵弾を発射
void EnemyBulletPool::Shoot(
    const Vector3& position,
    const Vector3& direction)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        // 未使用の弾を探す
        if (m_bullets[i]->IsActive() == false)
        {
            // 弾を再利用
            m_bullets[i]->Activate(position, direction);

            return;
        }
    }

    // 全弾使用中なら発射しない
    OutputDebugStringA("EnemyBulletPool: No available bullets\n");
}