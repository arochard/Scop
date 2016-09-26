#include "../includes/scop.h"

static void		projectionMatrix()
{
	float 		fov;
	float 		far;
	float 		near;
	float 		right, top;

	fov = 45.0f * M_PI / 180.0;
	printf("FOV %f\n", (1.0 / tan(fov)));
	far = 10.0;
	near = 0.5;
	right = 1.0;
	top = 1.0;

	g_projectionMatrix[0] = 1.0 / tan(fov);
	g_projectionMatrix[5] = (1920/1080) / tan(fov);
	g_projectionMatrix[10] = (far + near) / (far - near);
	g_projectionMatrix[14] = -2.0 * far * near / (far - near);
	g_projectionMatrix[11] = 1;
	g_projectionMatrix[15] = 0;

	printf("0 : %f , 5 : %f , 10 : %f , 11 : %f\n", g_projectionMatrix[0], g_projectionMatrix[5], g_projectionMatrix[10], g_projectionMatrix[11]);

}

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
	projectionMatrix();
}