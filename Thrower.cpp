#include "Thrower.h"
#include <GLFW/glfw3.h>

Thrower::Thrower() : MV_OBJ() {}

Thrower::Thrower(
	glm::vec3 pos_, 
	glm::vec3 direction_, 
	float speed_,
	VAO vao_
) : MV_OBJ(pos_, direction_, speed_, vao_) {}

void Thrower::InitTextures(Shader& shader) {
	Texture tex("assets/dchusky.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex.texUnit(shader, "assets/dchusky.png", 0);
	AddTexture(tex);
	SetCrntTexture(0);
}

void Thrower::MV() {
	pos += speed * direction;
	if (pos.x > 0.8f) {
		pos.x = 0.8f;
		direction.x = -direction.x;
	}
	else if (pos.x < -0.8f) {
		pos.x = -0.8f;
		direction.x = -direction.x;
	}
	transMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, pos);
}

void Thrower::event() {
	double t = glfwGetTime();
	if (t - lastTimeThrowFood > deltaTtoThrowFood) {
		SpriteManager::GetInstance().AddSprite(COIN, pos);
		lastTimeThrowFood = t;
		deltaTtoThrowFood = 0.1 + (rand() % 150) / 150.0;
	}
}