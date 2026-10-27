#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy.h" 

Game::Game()
{
}

bool Game::Start()
{
	m_player = NewGO<Player>(0, "player");
	m_player->SetName("player");

	m_bg = NewGO<BackGround>(0, "backGround");
	
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	m_enemy = NewGO<Enemy>(0, "enemy");

	return true;
}

Game::~Game()
{

}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{
	
}