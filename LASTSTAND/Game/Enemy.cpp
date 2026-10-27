#include "stdafx.h"
#include "Enemy.h"

bool Enemy::Start()
{
    m_position = Vector3(0.0f, 0.0f, 5000.0f);
    m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);

    // 敵モデルを読み込む
    m_modelRender.Init("Assets/modelData/enemy/enemy.tkm");
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();

    // 敵の当たり判定を初期化
    m_characterController.Init(80.0f, 200.0f, m_position);

    return true;
}

void Enemy::Update()
{
    m_position = m_characterController.Execute(m_moveSpeed,1.0f / 60.0f);

    m_modelRender.SetPosition(m_position);

    m_modelRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);
}