#pragma once

class Aim : public IGameObject
{
public:
    Aim();
    ~Aim();

    bool Start() override;
    void Render(RenderContext& rc) override;

    // 照準の表示切り替え
    void SetVisible(bool isVisible)
    {
        m_isVisible = isVisible;
    }

private:
    SpriteRender m_aimSprite;
    bool m_isVisible = false;
};