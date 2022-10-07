#ifndef MV_OBJ_H
#define MV_OBJ_H

#include<vector>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "Obj.h"
#include "VAO.h"
#include "EBO.h"
#include "Texture.h"


enum ObjType {
	THROWER,
	CATCHER,
	COIN
};


class MV_OBJ : public Obj
{
protected:
	float speed = 0.0f;
	glm::vec3 direction = glm::vec3();
public:
	MV_OBJ();
	MV_OBJ(
		glm::vec3 pos_,
		glm::vec3 direction_,
		float speed_,
		VAO vao_
	);
	virtual ~MV_OBJ();

	glm::vec3 getPos() { return pos; }

	virtual void MV();
	virtual void Collide(MV_OBJ*& other, int id);
	virtual void event();
	virtual void HandleState();

	glm::vec3 pos = glm::vec3();
	glm::vec3 size = glm::vec3(0.2f, 0.2f, 0.0f);
};

#endif