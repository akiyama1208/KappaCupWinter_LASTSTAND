#pragma once

class Title : public IGameObject
{
public:
    Title();
    ~Title();

    bool Start();
    void Update();
    void Render(RenderContext& rc) override;

private:
    SpriteRender spriteRender;
    SoundSource* titleBGM = nullptr;
};

