#ifndef OBJ_H
#define OBJ_H

#include<glm/glm.hpp>
#include "VAO.h"
#include "Texture.h"

class Obj
{
	bool deleted = true;
	int crntTexId = -1;
	std::vector<Texture> textures;
public:
	Obj();
	Obj(VAO vao_);

	VAO vao;
	virtual void InitTextures(Shader& shader);
	void AddTexture(Texture& tex);
	void SetCrntTexture(int id);
	int GetTexSize();
	void SetDeleted();
	Texture* GetCrntTexture();
	glm::mat4 transMatrix = glm::mat4(1.0f);
};

#endif

