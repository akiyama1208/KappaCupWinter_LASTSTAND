#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class Enemy;
class Enemy2;
class GameClear;
class GameOver;

class Game : public IGameObject
{
public:
    Game();
    ~Game();

    bool Start();
    void Update();
    void Render(RenderContext& rc);

private:
    GameOver* m_gameOver = nullptr;
    GameClear* m_gameClear = nullptr;

    Player* m_player = nullptr;
    BackGround* m_bg = nullptr;
    GameCamera* m_gameCamera = nullptr;

    // 敵
    Enemy* m_enemy = nullptr;
    Enemy2* m_enemy2 = nullptr;

    // Enemy2の出現管理
    bool m_isEnemy2Spawned = false;

    ModelRender m_modelRender;
    Vector3 m_pos;
};
