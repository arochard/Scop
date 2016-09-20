#include "../includes/scop.h"

static void		translation_right()
{
	// int i = 0;
	// while (i < 16)
	// {
	// 	printf("%f/", g_modelMatrix[i]);
	// 	printf("%f/", g_modelMatrix[i+1]);
	// 	printf("%f/", g_modelMatrix[i+2]);
	// 	printf("%f\n", g_modelMatrix[i+3]);
	// 	i = i + 4;
	// }
	g_modelMatrix[12] += 0.05;
}
static void		translation_left()
{
	g_modelMatrix[12] -= 0.05;
}
static void		translation_up()
{
	
}
static void		translation_down()
{
	
}

static void		scale_up()
{
	g_modelMatrix[0] *= 1.02;
	g_modelMatrix[5] *= 1.02;
	g_modelMatrix[10] *= 1.02;
}

static void		scale_down()
{
	g_modelMatrix[0] /= 1.02;
	g_modelMatrix[5] /= 1.02;
	g_modelMatrix[10] /= 1.02;
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