#pragma once

class Player;

class Enemy : public IGameObject
{
public:
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

    const Vector3& GetPosition() const
    {
        return m_position;
    }

    void TakeDamage(int damage);

    nsK2EngineLow::RigidBody* GetRigidBody()
    {
        return m_characterController.GetRigidBody();
    }

protected:
    ModelRender m_modelRender;
    CharacterController m_characterController;

    Vector3 m_position;
    Vector3 m_moveSpeed;

    Player* m_player = nullptr;

    float m_moveSpeedValue = 150.0f;

    int m_hp = 100;
};