#include "Obj.h"

Obj::Obj(){}

Obj::Obj(VAO vao_) : vao(vao_) {

}

void Obj::InitTextures(Shader& shader) {

}

void Obj::AddTexture(Texture& tex) {
	textures.push_back(tex);
}

void Obj::SetCrntTexture(int id) {
	crntTexId = id;
}

int Obj::GetTexSize()
{
	return textures.size();
}

void Obj::SetDeleted()
{
	deleted = true;
}

Texture* Obj::GetCrntTexture() {
	if (crntTexId == -1) return nullptr;
	return &textures[crntTexId];
}