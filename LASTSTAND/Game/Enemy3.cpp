#include "stdafx.h"
#include "Enemy3.h"
#include "Player.h"

bool Enemy3::Start()
{
    // HP
    m_hp = 200;
    m_maxHp = 200;

    // HP表示
    m_hpLabel = L"ENEMY3 HP";
    m_hpFontPosition = Vector3(-250.0f, 450.0f, 0.0f);

    // HPバー背景
    m_hpBarBackRender.Init("Assets/sprite/white.dds", 200.0f, 15.0f);
    m_hpBarBackRender.SetPivot(Vector2(0.0f, 0.5f));
    m_hpBarBackRender.SetPosition(Vector3(-30.0f, 430.0f, 0.0f));
    m_hpBarBackRender.SetMulColor(Vector4(0.3f, 0.3f, 0.3f, 1.0f));

    // HPバー本体
    m_hpBarRender.Init("Assets/sprite/white.dds", 200.0f, 15.0f);
    m_hpBarRender.SetPivot(Vector2(0.0f, 0.5f));
    m_hpBarRender.SetPosition(Vector3(-30.0f, 430.0f, 0.0f));
    m_hpBarRender.SetMulColor(Vector4(0.0f, 1.0f, 0.0f, 1.0f));

    // 初期位置
    m_position = Vector3(-1500.0f, 0.0f,7500.0f);
    m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);

    // 通常移動速度
    m_moveSpeedValue = 250.0f;

    // プレイヤーを取得
    m_player = FindGO<Player>("player");

    // モデル
    m_modelRender.Init("Assets/modelData/enemy/enemy.tkm");
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();

    // 当たり判定
    m_characterController.Init(125.0f, 200.0f, m_position);

    return true;
}

void Enemy3::Update()
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

    // 突進中の接触判定
    if (m_isCharging && !m_hasHitPlayer)
    {
        Vector3 distance = m_player->position - m_position;
        distance.y = 0.0f;

        if (distance.Length() < 300.0f)
        {
            m_player->TakeDamage(25);
            m_hasHitPlayer = true;
        }
    }

    m_position = m_characterController.Execute(m_moveSpeed,1.0f / 60.0f);

    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();

    // HPバー更新
    float hpRate = (float)m_hp / m_maxHp;

    m_hpBarRender.SetScale(Vector3(hpRate, 1.0f, 1.0f));

    if (hpRate > 0.5f)
    {
        m_hpBarRender.SetMulColor(Vector4(0.0f, 1.0f, 0.0f, 1.0f));
    }
    else if (hpRate > 0.25f)
    {
        m_hpBarRender.SetMulColor(Vector4(1.0f, 1.0f, 0.0f, 1.0f));
    }
    else if (hpRate > 0.0f)
    {
        m_hpBarRender.SetMulColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
    }

    m_hpBarBackRender.Update();
    m_hpBarRender.Update();
}

void Enemy3::Move()
{
    const float deltaTime = 1.0f / 60.0f;

    // プレイヤーへの方向
    Vector3 direction = m_player->position - m_position;
    direction.y = 0.0f;

    float distance = direction.Length();

    // 突進中
    if (m_isCharging)
    {
        m_chargeElapsed += deltaTime;

        // 突進速度
        m_moveSpeed = m_chargeDirection * 600.0f;

        // 突進終了
        if (m_chargeElapsed >= m_chargeDuration)
        {
            m_isCharging = false;
            m_chargeElapsed = 0.0f;
            m_chargeTimer = 0.0f;
        }

        return;
    }

    // 突進タイマー
    m_chargeTimer += deltaTime;

    // 3秒経過していて、プレイヤーが近くにいる場合
    if (m_chargeTimer >= m_chargeInterval &&
        distance > 300.0f &&
        distance < 1500.0f)
    {
        // 突進方向を決定
        direction.Normalize();
        m_chargeDirection = direction;

        m_isCharging = true;
        m_chargeElapsed = 0.0f;

        // 今回の突進ではまだダメージを与えていない
        m_hasHitPlayer = false;

        m_moveSpeed = m_chargeDirection * 600.0f;

        return;
    }

    // 通常追跡
    if (distance > 350.0f)
    {
        direction.Normalize();
        m_moveSpeed = direction * m_moveSpeedValue;
    }
    else
    {
        m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);
    }
}