#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include "SpriteManager.h"

class Game
{
    bool started = false;
    bool finished = false;
    double stTime;
    double totTime = 20.0f;
    double leftTime = 20.0f;
public:
    bool KeyA, KeyD;
    unsigned int Width, Height;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void Init();

    void ProcessInput();
    void Update();
    void Render();
};

#endif // !GAME_CLASS_H