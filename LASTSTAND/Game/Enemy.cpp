#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"

bool Enemy::Start()
{
    m_position = Vector3(0.0f, 0.0f, 5000.0f);
    m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);

    // プレイヤーを取得
    m_player = FindGO<Player>("player");

    // 敵モデルを読み込む
    m_modelRender.Init("Assets/modelData/enemy/enemy.tkm");
    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();

    // 当たり判定を初期化
    m_characterController.Init(125.0f, 200.0f, m_position);

    m_hpFontRender.SetPosition(m_hpFontPosition);

    return true;
}

void Enemy::Update()
{
    // プレイヤーがいなければ処理を終了
    if (m_player == nullptr)
    {
        return;
    }

    // プレイヤーがゲームオーバーなら敵を停止
    if (m_player->IsGameOver())
    {
        return;
    }

    // プレイヤーとの方向を計算
    Vector3 direction = m_player->position - m_position;
    direction.y = 0.0f;

    // 追跡を開始する距離
    float distance = direction.Length();
    float detectionRange = 1500.0f;

    // 一定距離以内なら追いかける
    if (distance <= detectionRange && distance > 300.0f)
    {
        direction.Normalize();
        m_moveSpeed = direction * m_moveSpeedValue;
    }
    else
    {
        // 遠いとき、または十分に近いときは停止
        m_moveSpeed = Vector3(0.0f, 0.0f, 0.0f);
    }

    m_position = m_characterController.Execute(
        m_moveSpeed,
        1.0f / 60.0f
    );

    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
    m_modelRender.Draw(rc);

    // 敵のHPを表示
    wchar_t hpText[64];
    swprintf_s(
        hpText,
        64,
        L"%ls: %d / %d",
        m_hpLabel,
        m_hp,
        m_maxHp
    );

    m_hpFontRender.SetPosition(m_hpFontPosition);
    m_hpFontRender.SetText(hpText);
    m_hpFontRender.Draw(rc);
}

void Enemy::TakeDamage(int damage)
{
    // すでに倒されていたら処理しない
    if (m_hp <= 0)
    {
        return;
    }

    // HPを減らす
    m_hp -= damage;

    // HPが0以下になったら
    if (m_hp <= 0)
    {
        m_hp = 0;

        OutputDebugStringA("Enemy deleted\n");

        DeleteGO(this);
        return;
    }

    // HPをログに表示
    char text[100];
    sprintf_s(text, "Enemy HP: %d\n", m_hp);
    OutputDebugStringA(text);
}