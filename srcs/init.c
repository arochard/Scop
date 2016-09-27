#include "../includes/scop.h"

// static void		projectionMatrix(t_data *data)
// {
// 	float 		fov;
// 	float 		zfar;
// 	float 		znear;
// 	float		zrange;
// 	float 		ar;

// 	ar = (float)data->width / (float)data->height;
// 	zfar = 100.0f;
// 	znear = 0.1f;
// 	zrange = znear - zfar;
// 	fov = tan((45.0f * M_PI / 180.0f) / 2.0) * znear;
// 	printf("FOV : %lf, tan(FOV) : %f\n", fov, (1.0f / tan(fov)));

// 	float sx = (2.0f * znear) / (fov * ar + fov * ar);
// 	float sy = znear / fov;
// 	float sz = -(zfar + znear) / (zfar - znear);
// 	float Pz = -(2.0f * zfar * znear) / (zfar - znear);

// 	// g_projectionMatrix[0] = 1.0f / tan(fov);
// 	// g_projectionMatrix[5] = (1920/1080) / tan(fov);
// 	// g_projectionMatrix[10] = (far + near) / (far - near);
// 	// g_projectionMatrix[14] = -2.0 * far * near / (far - near);
// 	// g_projectionMatrix[11] = 1;
// 	// g_projectionMatrix[15] = 0;

// 	g_projectionMatrix[0] = sx;
// 	g_projectionMatrix[1] = 0.0f;
// 	g_projectionMatrix[2] = 0.0f;
// 	g_projectionMatrix[3] = 0.0f;
// 	g_projectionMatrix[4] = 0.0f;
// 	g_projectionMatrix[5] = sy;
// 	g_projectionMatrix[6] = 0.0f;
// 	g_projectionMatrix[7] = 0.0f;
// 	g_projectionMatrix[8] = 0.0f;
// 	g_projectionMatrix[9] = 0.0f;
// 	g_projectionMatrix[10] = sz;
// 	g_projectionMatrix[11] = -1.0f;
// 	g_projectionMatrix[12] = 0.0f;
// 	g_projectionMatrix[13] = 0.0f;
// 	g_projectionMatrix[14] = Pz;
// 	g_projectionMatrix[15] = 0.0f;

// 	printf("0 : %f , 5 : %f , 10 : %f , 11 : %f\n", g_projectionMatrix[0], g_projectionMatrix[5], g_projectionMatrix[10], g_projectionMatrix[11]);

// }

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
	//projectionMatrix(data);
}