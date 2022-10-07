#ifndef BOMB_H
#define BOMB_H

#include "MV_OBJ.h"
class Bomb :
    public MV_OBJ
{
public:
	Bomb();
	Bomb(
		glm::vec3 pos_,
		glm::vec3 direction_,
		float speed_,
		VAO vao_
	);
	void InitTextures(Shader& shader);
	void MV();
};

#endif

