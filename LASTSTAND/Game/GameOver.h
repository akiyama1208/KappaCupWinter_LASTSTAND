#pragma once

class GameOver : public IGameObject
{
public:
    GameOver();
    ~GameOver();

    bool Start();
    void Update();
    void Render(RenderContext& rc);

private:
    FontRender m_fontRender;
};