#include "../includes/scop.h"



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	window = 0;
    if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
        printf("Bouhou %d %d\n", scancode, mods);
    if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
        printf("Bouhou %d %d\n", scancode, mods);
    if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
        printf("Bouhou %d %d\n", scancode, mods);
    if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
        printf("Bouhou %d %d\n", scancode, mods);
}