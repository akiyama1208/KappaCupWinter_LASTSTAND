#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class Enemy;
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
	Player* m_player;
	BackGround* m_bg = nullptr;
	GameCamera* m_gameCamera;
	Enemy* m_enemy = nullptr;
	ModelRender m_modelRender;
	Vector3 m_pos;
};

