#include "stdafx.h"
#include "Bullet.h"
#include "Enemy.h"
#include "physics/Physics.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

// プール用の初期化
void Bullet::InitPool()
{
    if (m_isInitialized)
    {
        return;
    }

    m_collider.Create(10.0f);

    m_modelRender.Init("Assets/modelData/bullet/bullet.tkm");

    m_isInitialized = true;
    m_isActive = false;
}

// 弾を発射する
void Bullet::Activate(const Vector3& position, const Vector3& direction)
{
    if (!m_isInitialized)
    {
        return;
    }

    m_position = position;
    m_direction = direction;
    m_direction.Normalize();

    // 寿命をリセット
    m_elapsedTime = 0.0f;

    // 弾を有効化
    m_isActive = true;

    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

// 弾を使用停止にする
void Bullet::Deactivate()
{
    m_isActive = false;
}

void Bullet::Update()
{
    // 使用中でなければ何もしない
    if (!m_isActive)
    {
        return;
    }

    const float deltaTime = 1.0f / 60.0f;

    m_elapsedTime += deltaTime;

    // 寿命が切れたら再利用可能にする
    if (m_elapsedTime >= m_lifeTime)
    {
        Deactivate();
        return;
    }

    Vector3 oldPosition = m_position;
    Vector3 newPosition = m_position + m_direction * m_speed * deltaTime;

    // 敵との当たり判定
    Enemy* enemy = FindGO<Enemy>("enemy");

    if (enemy != nullptr)
    {
        Vector3 toEnemy = enemy->GetPosition() - oldPosition;
        Vector3 move = newPosition - oldPosition;

        float moveLengthSq = move.Dot(move);
        float t = 0.0f;

        if (moveLengthSq > 0.0f)
        {
            t = toEnemy.Dot(move) / moveLengthSq;

            if (t < 0.0f) t = 0.0f;
            if (t > 1.0f) t = 1.0f;
        }

        Vector3 closestPosition = oldPosition + move * t;

        if ((enemy->GetPosition() - closestPosition).Length() < 135.0f)
        {
            enemy->TakeDamage(25);
            Deactivate();
            return;
        }
    }

    // 敵2との当たり判定
    Enemy* enemy2 = FindGO<Enemy>("enemy2");

    if (enemy2 != nullptr)
    {
        Vector3 toEnemy = enemy2->GetPosition() - oldPosition;
        Vector3 move = newPosition - oldPosition;

        float moveLengthSq = move.Dot(move);
        float t = 0.0f;

        if (moveLengthSq > 0.0f)
        {
            t = toEnemy.Dot(move) / moveLengthSq;

            if (t < 0.0f) t = 0.0f;
            if (t > 1.0f) t = 1.0f;
        }

        Vector3 closestPosition = oldPosition + move * t;

        if ((enemy2->GetPosition() - closestPosition).Length() < 135.0f)
        {
            enemy2->TakeDamage(25);
            Deactivate();
            return;
        }
    }

    // 壁との当たり判定
    Vector3 hitPos;

    if (PhysicsWorld::GetInstance()->RayTest(oldPosition, newPosition, hitPos))
    {
        Deactivate();
        return;
    }

    m_position = newPosition;

    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

void Bullet::Render(RenderContext& rc)
{
    // 使用中の弾だけ描画
    if (!m_isActive)
    {
        return;
    }

    m_modelRender.Draw(rc);
}