#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#define GLT_IMPLEMENTATION
#include<gltext/gltext.h>
#include<glm/gtc/type_ptr.hpp>
#include "Thrower.h"
#include "Catcher.h"
#include "Coin.h"
#include "Bomb.h"
#include "Shader.h"

enum EventType {
	IDLE,
	PRESS_D,
	PRESS_A,
};

class SpriteManager
{
	SpriteManager() {}

	Shader shader;

	Obj* background = nullptr;

	GLTtext* scoreText = nullptr;
	GLTtext* timeText = nullptr;
	GLTtext* hintText = nullptr;

	double lastBombTime = 0.0f;
	double bombTimeval = 1.5f;

	std::vector<MV_OBJ*> sprites[4];

	std::vector<Vertex> backgroundVerts = {
		Vertex{ glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
		Vertex{ glm::vec3(-1.0f, -0.2f, 0.0f), glm::vec2(0.0f, 1.0f) },
		Vertex{ glm::vec3( 1.0f, -0.2f, 0.0f), glm::vec2(1.0f, 1.0f) },
		Vertex{ glm::vec3( 1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f) },
	};

	std::vector<Vertex> vertices = {
		Vertex{ glm::vec3(-0.1f, -0.1f, 0.0f), glm::vec2(0.0f, 0.0f) },
		Vertex{ glm::vec3(-0.1f,  0.1f, 0.0f), glm::vec2(0.0f, 1.0f) },
		Vertex{ glm::vec3( 0.1f,  0.1f, 0.0f), glm::vec2(1.0f, 1.0f) },
		Vertex{ glm::vec3( 0.1f, -0.1f, 0.0f), glm::vec2(1.0f, 0.0f) },
	};

	std::vector<GLuint> indices = {
		0, 2, 1,
		0, 3, 2
	};

public:
	static SpriteManager& GetInstance() {
		static SpriteManager instance;
		return instance;
	}

	SpriteManager(SpriteManager const&) = delete;
	void operator=(SpriteManager const&) = delete;

	void InitText();
	void InitShader();

	void AddBackground();
	void AddSprite(enum ObjType type, glm::vec3 position);
	void SpawnBomb();

	void DelSprite(int group, int id);
	void DelOutOfBoundsCoinAndBomb();

	void DrawHintText();
	void DrawTitleText(double leftTime);
	void DrawAllSprite();

	void CollisionTest();

	void Update();
	void HandleEvent(enum EventType type);

	int CountScore();
	bool IsAllDead();
	
	void ClearAllPointer();
};

#endif
