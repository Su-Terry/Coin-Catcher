#define _CRT_SECURE_NO_WARNINGS
#include "SpriteManager.h"


void SpriteManager::InitText()
{
	gltInit();
	scoreText = gltCreateText();
	timeText = gltCreateText();
	hintText = gltCreateText();
	gltSetText(hintText, "Press A or D to MOVE!");
}

void SpriteManager::InitShader()
{
	//scoreboardShader.Load("scoreboard.vert", "scoreboard.frag");
	shader.Load("game.vert", "game.frag");
}

void SpriteManager::AddBackground()
{
	VAO vao;
	vao.Bind();
	VBO vbo(backgroundVerts);
	EBO ebo(indices);

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	Texture tex("desert.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	tex.texUnit(shader, "desert.png", 0);

	background = new Obj(vao);
	background->AddTexture(tex);
	background->SetCrntTexture(0);
}

void SpriteManager::AddSprite(enum ObjType type, glm::vec3 position)
{
	VAO vao;
	vao.Bind();
	VBO vbo(vertices);
	EBO ebo(indices);

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	switch (type) {
	case THROWER:
	{
		Thrower thrower(
			position,
			glm::vec3(1.0f, 0.0f, 0.0f),
			0.0003f,
			vao
		);
		thrower.InitTextures(shader);
		sprites[0].push_back(new Thrower(thrower));
	}
		break;
	case CATCHER:
	{
		Catcher catcher(
			position,
			glm::vec3(1.0f, 0.0f, 0.0f),
			0.0002f,
			vao
		);
		catcher.InitTextures(shader);
		sprites[1].push_back(new Catcher(catcher));
	}
		break;
	case COIN:
	{
		Coin coin(
			position,
			glm::vec3(0.0f, -1.0f, 0.0f),
			0.0005f,
			vao
		);
		coin.InitTextures(shader);
		sprites[2].push_back(new Coin(coin));
	}
		break;
	}
}

void SpriteManager::SpawnBomb()
{
	VAO vao;
	vao.Bind();
	VBO vbo(vertices);
	EBO ebo(indices);

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	float randX = (-6 + rand() % 13) / 10.0f;
	glm::vec3 position = glm::vec3(randX, 1.0f, 0.0f);

	Bomb bomb(
		position,
		glm::vec3(0.0f, -1.0f, 0.0f),
		0.0005f,
		vao
	);
	bomb.InitTextures(shader);
	sprites[2].push_back(new Bomb(bomb));
}

void SpriteManager::DelSprite(int group, int id)
{
	std::swap(sprites[group][id], sprites[group].back());
	delete sprites[group].back();
	sprites[group].pop_back();
}

void SpriteManager::DelOutOfBoundsCoinAndBomb()
{
	for (int t = 2; t <= 3; ++t) {
		for (int i = 0; i < sprites[t].size(); ++i) {
			if (sprites[t][i]->pos.y <= -1.0f) {
				DelSprite(t, i);
			}
		}
	}
}

void SpriteManager::DrawHintText()
{
	gltBeginDraw();

	gltColor(1.0f, 0.0f, 0.0f, 1.0f);
	gltDrawText2DAligned(hintText, 500.0f, 400.0f, 4.0f, GLT_CENTER, GLT_CENTER);

	gltEndDraw();
}

void SpriteManager::DrawTitleText(double leftTime)
{
	int score = CountScore();

	char scoreString[20];
	sprintf(scoreString, "Score: %d", score);
	gltSetText(scoreText, scoreString);

	char timeString[20];
	sprintf(timeString, "Time: %.2fs", leftTime);
	gltSetText(timeText, timeString);

	gltBeginDraw();

	gltColor(1.0f, 1.0f, 1.0f, 1.0f);
	gltDrawText2D(scoreText, 0.0f, 0.0f, 2.0f);
	gltDrawText2D(timeText, 800.0f, 0.0f, 2.0f);

	gltEndDraw();
}

void SpriteManager::DrawAllSprite()
{
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

	shader.Activate();
	Texture* backgroundTex = background->GetCrntTexture();
	if(backgroundTex)
		backgroundTex->Bind();
	background->vao.Bind();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translate"), 1, GL_FALSE, glm::value_ptr(background->transMatrix));
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
	
	if (backgroundTex)
		backgroundTex->Unbind();

	for (int t = 0; t < 3; ++t) {
		for (int i = 0; i < sprites[t].size(); ++i) {
			sprites[t][i]->HandleState();
			Texture* spriteTex = sprites[t][i]->GetCrntTexture();
			if (spriteTex)
				spriteTex->Bind();
			sprites[t][i]->vao.Bind();
			glUniformMatrix4fv(glGetUniformLocation(shader.ID, "translate"), 1, GL_FALSE, glm::value_ptr(sprites[t][i]->transMatrix));
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
			if (spriteTex)
				spriteTex->Unbind();
		}
	}
}

int SpriteManager::CountScore()
{
	int score = 0;
	for (int i = 0; i < sprites[1].size(); ++i) {
		score += ((Catcher*)sprites[1][i])->GetScore();
	}
	return score;
}

void SpriteManager::Update()
{
	double crntTime = glfwGetTime();
	if (crntTime - lastBombTime >= bombTimeval) {
		SpawnBomb();
		lastBombTime = crntTime;
	}
	DelOutOfBoundsCoinAndBomb();
	for (int t = 0; t < 3; ++t) {
		for (int i = 0; i < sprites[t].size(); ++i) {
			sprites[t][i]->event();
			sprites[t][i]->MV();
		}
	}
}

void SpriteManager::ClearAllPointer()
{
	gltDeleteText(scoreText);
	gltDeleteText(timeText);
	gltDeleteText(hintText);
	gltTerminate();
}

bool SpriteManager::IsAllDead()
{
	bool isAlive = true;
	for (int i = 0; i < sprites[1].size(); ++i) {
		if (((Catcher*)sprites[1][i])->IsDead())
			isAlive = false;
	}
	return !isAlive;
}

void SpriteManager::CollisionTest()
{
	for (int i = 0; i < sprites[1].size(); ++i) {
		for (int t = 2; t <= 3; ++t) {
			for (int j = 0; j < sprites[t].size(); ++j) {
				bool collisionX = sprites[1][i]->pos.x + sprites[1][i]->size.x >= sprites[t][j]->pos.x &&
					sprites[t][j]->pos.x + sprites[t][j]->size.x >= sprites[1][i]->pos.x;
				bool collisionY = sprites[1][i]->pos.y + sprites[1][i]->size.y >= sprites[t][j]->pos.y &&
					sprites[t][j]->pos.y + sprites[t][i]->size.y >= sprites[1][i]->pos.y;

				if (collisionX && collisionY) {
					sprites[1][i]->Collide(sprites[t][j], j);
				}
			}
		}
	}
}

void SpriteManager::HandleEvent(enum EventType type)
{
	for (int i = 0; i < sprites[1].size(); ++i) {
		Catcher* cptr = dynamic_cast<Catcher*>(sprites[1][i]);
		if (cptr) {
			switch (type) {
			case IDLE:
				break;
			case PRESS_A:
				cptr->MV(glm::vec3(-1.0f, 0.0f, 0.0f));
				break;
			case PRESS_D:
				cptr->MV(glm::vec3(1.0f, 0.0f, 0.0f));
				break;
			}
		}
	}
}
