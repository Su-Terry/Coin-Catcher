#include "Game.h"

Game::Game(unsigned int width, unsigned int height)
	: Width(width), Height(height), State(PLAY), KeyA(false), KeyD(false) {
}

Game::~Game()
{
}

void Game::SetGameWindow(GLFWwindow** window_)
{
	window = window_;
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
	SpriteManager::GetInstance().Update();
	Render();
	if (!started) {
		SpriteManager::GetInstance().DrawHintText();
		if (KeyA || KeyD) {
			started = true;
			stTime = glfwGetTime();
		}
	}
	else if (SpriteManager::GetInstance().IsAllDead()) {
		std::cout << "Popcat is dead!" << std::endl;
		glfwSetWindowShouldClose(*window, true);
		int score = SpriteManager::GetInstance().CountScore();
		std::cout << "Your score is: " << score << std::endl;
	}
	else {
		leftTime = totTime + stTime - glfwGetTime();
		if (leftTime >= 0.0f) {
			SpriteManager::GetInstance().CollisionTest();
			ProcessInput();
		}
		else {
			std::cout << "Time's up!" << std::endl;
			glfwSetWindowShouldClose(*window, true);
			int score = SpriteManager::GetInstance().CountScore();
			std::cout << "Your score is: " << score << std::endl;
		}
	}
}

void Game::Render()
{
	SpriteManager::GetInstance().DrawAllSprite();
	SpriteManager::GetInstance().DrawTitleText(leftTime);
}
