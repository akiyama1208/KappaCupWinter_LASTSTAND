#pragma once

class GameClear : public IGameObject
{
public:
    GameClear();
    ~GameClear();

    bool Start();
    void Update();
    void Render(RenderContext& rc);

    // タイトルに戻る要求を取得
    bool IsRetry() const
    {
        return m_isRetry;
    }

private:
    SpriteRender m_spriteRender;
    bool m_isRetry = false;
};

