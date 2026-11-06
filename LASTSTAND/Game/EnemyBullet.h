#pragma once
#include "physics/SphereCollider.h"

class Player;

class EnemyBullet : public IGameObject
{
public:
    EnemyBullet();
    ~EnemyBullet();
    // 初期化
    void Init(const Vector3& position, const Vector3& direction);
    // 更新処理
    void Update();
    // 描画処理
    void Render(RenderContext& rc);
    // 弾を使用状態にする
    void Activate(const Vector3& position, const Vector3& direction);
    // 弾を未使用状態に戻す
    void Deactivate();
    // 使用中かどうか
    bool IsActive() const
    {
        return m_isActive;
    }

private:
    ModelRender m_modelRender;       // 弾のモデル
    Vector3 m_position;              // 弾の位置
    Vector3 m_direction;             // 弾の進行方向

    
    float m_speed = 2000.0f;         // 弾の速度
    float m_lifeTime = 3.0f;         // 弾の寿命
    float m_elapsedTime = 0.0f;      // 経過時間

    bool m_isActive = false;         // 使用中かどうか
    
    Player* m_player = nullptr;      // プレイヤー

    nsK2EngineLow::SphereCollider m_collider;   // 当たり判定
};

