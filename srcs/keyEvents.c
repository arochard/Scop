#include "../includes/scop.h"

static void		translation_right()
{
	int i = 0;
	while (i < 16)
	{
		printf("%f/", g_modelMatrix[i]);
		printf("%f/", g_modelMatrix[i+1]);
		printf("%f/", g_modelMatrix[i+2]);
		printf("%f\n", g_modelMatrix[i+3]);
		i = i + 4;
	}
	g_modelMatrix[3] += 0.3;
}
static void		translation_left()
{
	g_modelMatrix[3] -= 0.3;
}
static void		translation_up()
{
	
}
static void		translation_down()
{
	
}

void 			key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	window = 0;
	scancode = 0;
	mods = 0;
	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
		translation_right();
	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
		translation_left();
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
		translation_up();
	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
		translation_down();
}