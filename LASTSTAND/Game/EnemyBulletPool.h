#pragma once
#include "EnemyBullet.h"

class EnemyBulletPool : public IGameObject
{
public:
    EnemyBulletPool();
    ~EnemyBulletPool();

    // 初期化
    bool Start() override;

    // 敵弾を発射する
    void Shoot(
        const Vector3& position,
        const Vector3& direction
    );

private:
    // 敵弾の最大数
    static const int MAX_BULLETS = 30;

    // 敵弾の配列
    EnemyBullet* m_bullets[MAX_BULLETS];

    // 敵弾の初期化
    void InitBullets();
};

