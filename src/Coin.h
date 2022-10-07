#ifndef COIN_H
#define COIN_H

#include "MV_OBJ.h"

class Coin : public MV_OBJ
{
	int score = 0;
public:
	Coin();
	Coin(
		glm::vec3 pos_,
		glm::vec3 direction_,
		float speed_,
		VAO vao_
	);
	void InitTextures(Shader& shader);
	void MV();
	int GetScore();
};

#endif
