#include "../includes/scop.h"


void 			key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	window = 0;
	scancode = 0;
	mods = 0;
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		g_is_texture = (g_is_texture == 0)? 1 : 0;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		exit(0);
	if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		g_modelMatrix[12] += 0.05;
	if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
		g_modelMatrix[12] -= 0.05;
	if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
		g_modelMatrix[13] += 0.05;
	if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
		g_modelMatrix[13] -= 0.05;
	if (key == GLFW_KEY_PAGE_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
		g_modelMatrix[14] += 0.05;
	if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
		g_modelMatrix[14] -= 0.05;
}