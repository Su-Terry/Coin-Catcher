#ifndef THROWER_H
#define THROWER_H

#include "MV_OBJ.h"
#include "SpriteManager.h"

const glm::vec3 DC_HUSKY_POS = glm::vec3(0.0f, 0.7f, 0.0f);

class Thrower : public MV_OBJ
{
	double deltaTtoThrowFood = 0.0;
	double lastTimeThrowFood = 0.0;
public:
	Thrower();
	Thrower(
		glm::vec3 pos_,
		glm::vec3 direction_,
		float speed_,
		VAO vao_
	);
	void InitTextures(Shader& shader);
	void MV();
	void event();
};

#endif