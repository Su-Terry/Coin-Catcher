#include "Coin.h"

Coin::Coin() : MV_OBJ() {}

Coin::Coin(
	glm::vec3 pos_,
	glm::vec3 direction_,
	float speed_,
	VAO vao_
) : MV_OBJ(pos_, direction_, speed_, vao_) {}

void Coin::InitTextures(Shader& shader) {
	int id = rand() % 3;
	switch (id) {
	case 0:
	{
		Texture tex1("chicken_meat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		tex1.texUnit(shader, "chicken_meat.png", 0);
		AddTexture(tex1);
		score = 10;
	}
		break;
	case 1:
	{
		Texture tex2("lamp.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		tex2.texUnit(shader, "lamp.png", 0);
		AddTexture(tex2);
		score = 3;
	}
		break;
	case 2:
	{
		Texture tex3("hamberger.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
		tex3.texUnit(shader, "hamberger.png", 0);
		AddTexture(tex3);
		score = 6;
	}
		break;

	}
	SetCrntTexture(0);
}

void Coin::MV() {
	pos += speed * direction;
	transMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, pos);
}

int Coin::GetScore()
{
	return score;
}
