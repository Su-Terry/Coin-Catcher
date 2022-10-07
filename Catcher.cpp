#include "Catcher.h"

void Catcher::Eat()
{
	eating = true;
	stT = clock();
	SetCrntTexture(0);
}

void Catcher::Idle()
{
	SetCrntTexture(1);
}

void Catcher::Dead()
{
	isDead = true;
	SetCrntTexture(2);
}

Catcher::Catcher() : MV_OBJ() {}

Catcher::Catcher(
	glm::vec3 pos_,
	glm::vec3 direction_,
	float speed_,
	VAO vao_
) : MV_OBJ(pos_, direction_, speed_, vao_) {}

void Catcher::InitTextures(Shader& shader) {
	Texture tex1("popcat_idle.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex1.texUnit(shader, "popcat_idle.png", 0);
	AddTexture(tex1);
	
	Texture tex2("popcat_eat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex2.texUnit(shader, "popcat_eat.png", 0);
	AddTexture(tex2);
	SetCrntTexture(1);
	
	Texture tex3("popcat_dead.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex3.texUnit(shader, "popcat_dead.png", 0);
	AddTexture(tex3);
}

void Catcher::MV(glm::vec3 direction) {
	pos += speed * direction;
	if (pos.x > 0.9f) {
		pos.x = 0.9f;
	} 
	else if (pos.x < -0.9f) {
		pos.x = -0.9f;
	}
	transMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, pos);
}

void Catcher::Collide(MV_OBJ*& other, int id) {
	Coin* cptr = dynamic_cast<Coin*>(other);
	Bomb* bptr = dynamic_cast<Bomb*>(other);
	if (cptr) {
		score += cptr->GetScore();
		Eat();
		SpriteManager::GetInstance().DelSprite(2, id);
	}
	else if (bptr) {
		bptr->SetCrntTexture(1);
		Dead();
	}
}

void Catcher::HandleState()
{
	double crntTime = clock();
	if (!isDead && eating && crntTime - stT > deltaT) {
		Idle();
	}
}

int Catcher::GetScore()
{
	return score;
}

bool Catcher::IsDead()
{
	return isDead;
}
