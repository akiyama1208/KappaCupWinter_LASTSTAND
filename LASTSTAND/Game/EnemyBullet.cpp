#include "stdafx.h"
#include "EnemyBullet.h"
#include "Player.h"
#include "physics/Physics.h"
#include "sound/SoundSource.h"

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

// 初期化
void EnemyBullet::Init(
    const Vector3& position,
    const Vector3& direction)
{
    m_collider.Create(10.0f);

    m_modelRender.Init("Assets/modelData/enemybullet/enemybullet.tkm");

    m_position = position;
    m_direction = direction;
    m_direction.Normalize();

    m_elapsedTime = 0.0f;
    m_isActive = false;

    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

// 弾を使用状態にする
void EnemyBullet::Activate(
    const Vector3& position,
    const Vector3& direction)
{
    m_position = position;

    m_direction = direction;
    m_direction.Normalize();

    m_elapsedTime = 0.0f;
    m_isActive = true;

    m_player = FindGO<Player>("player");

    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

// 弾を未使用状態に戻す
void EnemyBullet::Deactivate()
{
    m_isActive = false;
}

// 更新処理
void EnemyBullet::Update()
{
    // 未使用なら何もしない
    if (m_isActive == false)
    {
        return;
    }

    // プレイヤーがいなければ終了
    if (m_player == nullptr)
    {
        Deactivate();
        return;
    }

    // ゲームオーバーなら弾を停止
    if (m_player->IsGameOver())
    {
        Deactivate();
        return;
    }

    const float deltaTime = 1.0f / 60.0f;

    // 経過時間
    m_elapsedTime += deltaTime;

    // 寿命が切れたら未使用に戻す
    if (m_elapsedTime >= m_lifeTime)
    {
        Deactivate();
        return;
    }

    // 移動前の位置
    Vector3 oldPosition = m_position;

    // 移動後の位置
    Vector3 newPosition =
        m_position + m_direction * m_speed * deltaTime;

    // プレイヤーとの当たり判定
    Vector3 toPlayer = m_player->position - oldPosition;
    Vector3 move = newPosition - oldPosition;

    float moveLengthSq = move.Dot(move);
    float t = 0.0f;

    if (moveLengthSq > 0.0f)
    {
        t = toPlayer.Dot(move) / moveLengthSq;

        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
    }

    Vector3 closestPosition = oldPosition + move * t;

    // プレイヤーのカプセル半径125 + 弾の半径10
    if ((m_player->position - closestPosition).Length() < 50.0f)
    {
        // 被弾SEを再生
        SoundSource* se = NewGO<SoundSource>(0);
        se->Init(5);
        se->SetVolume(3.5f);
        se->Play(false);

        // プレイヤーに25ダメージ
        m_player->TakeDamage(25);

        // 弾を未使用状態に戻す
        Deactivate();
        return;
    }

    // 壁との当たり判定
    Vector3 hitPos;

    if (PhysicsWorld::GetInstance()->RayTest(
        oldPosition,
        newPosition,
        hitPos))
    {
        Deactivate();
        return;
    }

    // 位置を更新
    m_position = newPosition;

    m_modelRender.SetPosition(m_position);
    m_modelRender.Update();
}

// 描画処理
void EnemyBullet::Render(RenderContext& rc)
{
    if (m_isActive == false)
    {
        return;
    }

    m_modelRender.Draw(rc);
}