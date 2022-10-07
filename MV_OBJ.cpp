#include "MV_OBJ.h"

MV_OBJ::MV_OBJ() { }

MV_OBJ::MV_OBJ(
	glm::vec3 pos_, 
	glm::vec3 direction_, 
	float speed_,
	VAO vao_
) : Obj(vao_), pos(pos_), direction(direction_), speed(speed_) {
}

MV_OBJ::~MV_OBJ()
{
}

void MV_OBJ::MV() {
	transMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, pos);
}

void MV_OBJ::Collide(MV_OBJ*& other, int id)
{
}

void MV_OBJ::event()
{
}

void MV_OBJ::HandleState()
{
}
