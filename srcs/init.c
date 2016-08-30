#include "../includes/scop.h"

// static int		get_key(int keycode, void *param)
// {
// 	if (keycode == ESCAPE)
// 		exit(0);

// 	param = param + 3;

// 	return (0);
// }

// static int		expose_hook(t_data *data)
// {
// 	loading_buffer(data);
// 	draw(data);
// 	return (0);
// }

void			init_window(t_data *data)
{
	if (!glfwInit ())
	{
		fprintf (stderr, "ERROR: could not start GLFW3\n");
		exit(0);
	}
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	data->win_ptr = glfwCreateWindow (1920, 1080, "Scop", NULL, NULL);
	if (!data->win_ptr)
	{
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		exit(0);
	}
	glfwMakeContextCurrent (data->win_ptr);
	glewExperimental = GL_TRUE;
	glewInit ();
}