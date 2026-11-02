#pragma once

class Player;

class Enemy : public IGameObject
{
public:
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

    // 敵の位置を取得
    const Vector3& GetPosition() const
    {
        return m_position;
    }

    // ダメージ処理
    void TakeDamage(int damage);

    // 敵の物理オブジェクトを取得
    nsK2EngineLow::RigidBody* GetRigidBody()
    {
        return m_characterController.GetRigidBody();
    }

private:
    ModelRender m_modelRender;
    CharacterController m_characterController;

    Vector3 m_position;
    Vector3 m_moveSpeed;

    // プレイヤー
    Player* m_player = nullptr;

    // 敵の移動速度
    float m_moveSpeedValue = 150.0f;

    // 敵のHP
    int m_hp = 100;
};