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

void Bullet::Init(const Vector3& position,const Vector3& direction)
{
    // 発射位置を設定
    m_position = position;

    // 発射方向を設定
    m_direction = direction;
    m_direction.Normalize();

    m_collider.Create(10.0f);

    m_modelRender.Init("Assets/modelData/bullet/bullet.tkm");
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

void Bullet::Update()
{
    const float deltaTime = 1.0f / 60.0f;

    m_elapsedTime += deltaTime;

    if (m_elapsedTime >= m_lifeTime)
    {
        DeleteGO(this);
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

        // 敵のカプセル半径125 + 弾の半径10
        if ((enemy->GetPosition() - closestPosition).Length() < 135.0f)
        {
            OutputDebugStringA("Bullet hit!\n");

            enemy->TakeDamage(25);
            DeleteGO(this);
            return;
        }
    }

    // 壁との当たり判定
    Vector3 hitPos;

    if (PhysicsWorld::GetInstance()->RayTest(oldPosition, newPosition, hitPos))
    {
        DeleteGO(this);
        return;
    }

    m_position = newPosition;
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

void Bullet::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);
}