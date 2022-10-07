#include "Bomb.h"

Bomb::Bomb() : MV_OBJ() {}

Bomb::Bomb(
	glm::vec3 pos_,
	glm::vec3 direction_,
	float speed_,
	VAO vao_
) : MV_OBJ(pos_, direction_, speed_, vao_) {}

void Bomb::InitTextures(Shader& shader)
{
	Texture tex1("bomb.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex1.texUnit(shader, "bomb.png", 0);
	AddTexture(tex1);

	SetCrntTexture(0);
}

void Bomb::MV()
{
	pos += speed * direction;
	transMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, pos);
}
