#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include "SpriteManager.h"

enum GameState {
    PLAY,
    END,
};

class Game
{
    bool started = false;
    double stTime;
    double totTime = 20.0f;
    double leftTime = 20.0f;
    GLFWwindow** window;
public:
    GameState State;
    bool KeyA, KeyD;
    unsigned int Width, Height;

    Game(unsigned int width, unsigned int height);
    ~Game();

    void SetGameWindow(GLFWwindow** window_);

    void Init();

    void ProcessInput();
    void Update();
    void Render();
};

#endif // !GAME_CLASS_H