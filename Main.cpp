/*
 * Author: 110550141
 * Name: 蘇智海
*/
#include "Game.h"

const int WIDTH = 1000;
const int HEIGHT = 800;

Game CoinCollector(WIDTH, HEIGHT);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		CoinCollector.KeyD = true;
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		CoinCollector.KeyD = false;
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		CoinCollector.KeyA = true;
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		CoinCollector.KeyA = false;
}

int main() {
	srand(time(NULL));
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Coin Collector - 110550141", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glfwSetKeyCallback(window, key_callback);

	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	CoinCollector.Init();

	while (!glfwWindowShouldClose(window)) {
		//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		CoinCollector.Update();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	SpriteManager::GetInstance().ClearAllPointer();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}