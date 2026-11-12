#pragma once

class HowToPlay : public IGameObject
{
public:
    HowToPlay() {}
    ~HowToPlay() {}

    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;

private:
    SpriteRender m_spriteRender;
};
