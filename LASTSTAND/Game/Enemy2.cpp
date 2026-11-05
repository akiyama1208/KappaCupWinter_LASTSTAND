#include "stdafx.h"
#include "Enemy2.h"
#include "Player.h"

bool Enemy2::Start()
{
    // 初期位置
    m_position = Vector3(4000.0f, 0.0f,500.0f);

    m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);

    // プレイヤーを取得
    m_player = FindGO<Player>("player");

    // 2体目のモデルを読み込む
    m_modelRender.Init("Assets/modelData/enemy2/enemy2.tkm");
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();

    // 当たり判定
    m_characterController.Init(125.0f, 200.0f, m_position);

    // HP
    m_hp = 150;

    return true;
}

void Enemy2::Update()
{
    if (m_player == nullptr)
    {
        return;
    }

    if (m_player->IsGameOver())
    {
        return;
    }

    Move();
    Attack();

    m_position = m_characterController.Execute(
        m_moveSpeed,
        1.0f / 60.0f
    );

    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

void Enemy2::Move()
{
    // プレイヤーとの方向を計算
    Vector3 direction = m_player->position - m_position;
    direction.y = 0.0f;

    float distance = direction.Length();

    if (distance < 1500.0f)
    {
        // 近すぎる場合は後退
        direction.Normalize();
        m_moveSpeed = direction * -m_moveSpeedValue;
    }
    else
    {
        //1500以上離れていたら停止
        m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);
    }
}

void Enemy2::Attack()
{
    // 攻撃処理は後で実装
}