#pragma once
#include "Enemy.h"

class EnemyBulletPool;

class Enemy2 : public Enemy
{
public:
    bool Start() override;
    void Update() override;

private:
    void Move();
    void Attack();

    // 敵弾プール
    EnemyBulletPool* m_enemyBulletPool = nullptr;

    // 攻撃間隔
    float m_attackTimer = 0.0f;

    // 攻撃するまでの時間
    float m_attackInterval = 3.0f;
};