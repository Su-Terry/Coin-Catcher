#include "Game.h"

Game::Game(unsigned int width, unsigned int height)
	: Width(width), Height(height), KeyA(false), KeyD(false) {
}

Game::~Game()
{
}

void Game::Init()
{
	SpriteManager::GetInstance().InitShader();
	SpriteManager::GetInstance().InitText();
	SpriteManager::GetInstance().AddBackground();
	SpriteManager::GetInstance().AddSprite(THROWER, DC_HUSKY_POS);
	SpriteManager::GetInstance().AddSprite(CATCHER, MEOW_POS);
}

void Game::ProcessInput()
{
	if (KeyA && !KeyD)
		SpriteManager::GetInstance().HandleEvent(PRESS_A);
	else if (!KeyA && KeyD)
		SpriteManager::GetInstance().HandleEvent(PRESS_D);
	else
		SpriteManager::GetInstance().HandleEvent(IDLE);
}

void Game::Update()
{
	SpriteManager::GetInstance().MV();
	Render();
	if (finished) {
		SpriteManager::GetInstance().DrawFinalScoreText();
	}
	else {
		SpriteManager::GetInstance().Update();
		if (!started) {
			SpriteManager::GetInstance().DrawHintText();
			if (KeyA || KeyD) {
				started = true;
				stTime = glfwGetTime();
			}
		}
		else if (SpriteManager::GetInstance().IsAllDead()) {
			finished = true;
		}
		else {
			leftTime = totTime + stTime - glfwGetTime();
			leftTime = (leftTime > 0) ? leftTime : 0;
			if (leftTime > 0) {
				SpriteManager::GetInstance().CollisionTest();
				ProcessInput();
			}
			else {
				finished = true;
			}
		}
	}
}

void Game::Render()
{
	SpriteManager::GetInstance().DrawAllSprite();
	SpriteManager::GetInstance().DrawTitleText(leftTime);
}
