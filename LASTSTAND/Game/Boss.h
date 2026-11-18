#pragma once
#include "Enemy.h"

class EnemyBulletPool;

class Boss : public Enemy
{
public:
    bool Start() override;
    void Update() override;

private:
    void Move();
    void Attack();

    EnemyBulletPool* m_enemyBulletPool = nullptr;

    // 遠距離攻撃
    float m_attackTimer = 0.0f;
    float m_attackInterval = 2.5f;

    // 突進攻撃
    float m_chargeTimer = 0.0f;
    float m_chargeInterval = 5.0f;
    float m_chargeDuration = 1.0f;
    float m_chargeElapsed = 0.0f;

    bool m_isCharging = false;
    bool m_hasHitPlayer = false;
    Vector3 m_chargeDirection;

    // 近距離攻撃
    float m_meleeTimer = 0.0f;
    float m_meleeInterval = 1.5f;
};