#ifndef CATCHER_H
#define CATCHER_H

#include<ctime>
#include "MV_OBJ.h"
#include "SpriteManager.h"

const glm::vec3 MEOW_POS = glm::vec3(0.0f, -0.8f, 0.0f);

class Catcher : public MV_OBJ
{
	int score = 0;
	bool isDead = false;
	double eating = false;
	double stT = 0.0;
	double deltaT = 200;
	void Eat();
	void Idle();
	void Dead();
public:
	Catcher();
	Catcher(
		glm::vec3 pos_,
		glm::vec3 direction_,
		float speed_,
		VAO vao_
	);

	void InitTextures(Shader& shader);
	void MV(glm::vec3 direction);
	void Collide(MV_OBJ*& other, int id);
	void HandleState();
	int GetScore();
	bool IsDead();
};

#endif

