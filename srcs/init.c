#include "../includes/scop.h"

void			read_shaders(const char **str, char *file)
{
	FILE		*fp;
	long 		fsize;
	char		*tmp;

	fp = fopen(file, "r");
	if (fp == NULL)
	{
		printf("Error read shader file\n");
		exit(0);
	}
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	rewind(fp);
	tmp = (char*)malloc(sizeof(char) * (fsize + 1));
	fread(tmp, 1, fsize, fp);
	fclose(fp);
	tmp[fsize] = 0;
	*str = (const char*)tmp;
}

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
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	data->win_ptr = glfwCreateWindow (data->width, data->height, "Scop", NULL, NULL);
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