#include "../includes/scop.h"

static void		translation_right()
{
	g_modelMatrix[12] += 0.05;
}
static void		translation_left()
{
	g_modelMatrix[12] -= 0.05;
}
static void		translation_up()
{
	g_modelMatrix[13] += 0.05;
}
static void		translation_down()
{
	g_modelMatrix[13] -= 0.05;
}

static void		scale_up()
{
	g_modelMatrix[14] += 0.05;
}

static void		scale_down()
{
	g_modelMatrix[14] -= 0.05;
}

void 			key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	window = 0;
	scancode = 0;
	mods = 0;
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		translation_right();
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		translation_left();
	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
		translation_up();
	if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
		translation_down();
	if (key == GLFW_KEY_PAGE_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
		scale_up();
	if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
		scale_down();
}