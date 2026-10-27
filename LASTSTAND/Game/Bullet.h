#pragma once

class Bullet : public IGameObject
{
public:
    Bullet();
    ~Bullet();

    // 弾の初期化
    void Init(const Vector3& position, const Vector3& direction);
    // 更新処理
    void Update();
    // 描画処理
    void Render(RenderContext& rc);

    // 弾の位置を取得
    const Vector3& GetPosition() const
    {
        return m_position;
    }

private:
    // 弾のモデル
    ModelRender m_modelRender;
    // 弾の位置
    Vector3 m_position;
    // 弾の進行方向
    Vector3 m_direction;
    // 弾の速度
    float m_speed = 3000.0f;
    // 弾の寿命
    float m_lifeTime = 1.0f;
    // 経過時間
    float m_elapsedTime = 0.0f;
};

