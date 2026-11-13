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

    // 現在のHPを取得
    int GetHP() const
    {
        return m_hp;
    }

    // 最大HPを取得
    int GetMaxHP() const
    {
        return m_maxHp;
    }

    nsK2EngineLow::RigidBody* GetRigidBody()
    {
        return m_characterController.GetRigidBody();
    }

protected:
    ModelRender m_modelRender;
    CharacterController m_characterController;

    // 敵のHP表示
    FontRender m_hpFontRender;

    // 敵のHPバー
    SpriteRender m_hpBarBackRender;
    SpriteRender m_hpBarRender;

    // HP表示位置
    Vector3 m_hpFontPosition = Vector3(-250.0f,500.0f, 0.0f);

    // HP表示の名前
    const wchar_t* m_hpLabel = L"ENEMY HP";

    Vector3 m_position;
    Vector3 m_moveSpeed;

    Player* m_player = nullptr;

    float m_moveSpeedValue = 150.0f;

    // HP
    int m_hp = 100;
    int m_maxHp = 100;
};