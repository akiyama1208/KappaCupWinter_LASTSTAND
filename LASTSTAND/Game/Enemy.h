#pragma once

class Enemy : public IGameObject
{
public:
    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

private:
    ModelRender m_modelRender;

    CharacterController m_characterController;

    // 敵の位置と移動速度
    Vector3 m_position;
    Vector3 m_moveSpeed;
};
