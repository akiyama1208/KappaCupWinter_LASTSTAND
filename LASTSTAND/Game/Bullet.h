#pragma once
#include "physics/SphereCollider.h"

class Bullet : public IGameObject
{
public:
    Bullet();
    ~Bullet();

    // プール用の初期化
    void InitPool();
    // 弾を発射可能な状態にする
    void Activate(const Vector3& position, const Vector3& direction);
    // 弾を使用停止にする
    void Deactivate();
    // 更新処理
    void Update();
    // 描画処理
    void Render(RenderContext& rc);
    // 使用中かどうか
    bool IsActive() const
    {
        return m_isActive;
    }
    // 弾の位置を取得
    const Vector3& GetPosition() const
    {
        return m_position;
    }

private:
    ModelRender m_modelRender;

    Vector3 m_position;
    Vector3 m_direction;

    float m_speed = 3000.0f;
    float m_lifeTime = 1.0f;
    float m_elapsedTime = 0.0f;

    bool m_isActive = false;
    bool m_isInitialized = false;

    nsK2EngineLow::SphereCollider m_collider;
};
