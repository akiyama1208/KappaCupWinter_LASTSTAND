#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init(
    const Vector3& position,
    const Vector3& direction)
{
    // 発射位置を設定
    m_position = position;

    // 発射方向を設定
    m_direction = direction;
    m_direction.Normalize();

    m_modelRender.Init("Assets/modelData/bullet/bullet.tkm");
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

void Bullet::Update()
{
    // 1フレームの時間
    const float deltaTime = 1.0f / 60.0f;

    // 経過時間を更新
    m_elapsedTime += deltaTime;

    // 寿命が尽きたら削除
    if (m_elapsedTime >= m_lifeTime)
    {
        DeleteGO(this);
        return;
    }

    // 弾を前方へ移動
    m_position += m_direction * m_speed * deltaTime;

    // モデルの位置を更新
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

void Bullet::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);
}