class GameOver : public IGameObject
{
public:
    GameOver();
    ~GameOver();

    bool Start();
    void Update();
    void Render(RenderContext& rc);

    // リトライ要求を取得
    bool IsRetry() const
    {
        return m_isRetry;
    }

private:
    SpriteRender m_spriteRender;
    bool m_isRetry = false;
};