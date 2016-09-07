#include "../includes/scop.h"

GLfloat				g_modelMatrix[16] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
GLfloat				g_viewMatrix[16] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};
GLfloat				g_projectionMatrix[16] = {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0};

int			main(int argc, char **argv)
{
	t_data		data;

	if (argc == 3)
	{
		data.fileObj = argv[1];
		data.fileMtl = argv[2];
	}
	else
	{
		printf("Usage: ./Scop [obj file] [mtl file]");
		exit(0);
	}
	read_shaders(&data.vertex_shader, VS);
	read_shaders(&data.fragment_shader, FS);
	printf("%s\n", data.vertex_shader);
	printf("%s\n", data.fragment_shader);
	parserObj(&data);
	init_window(&data);
	init_matrix();
	loading_buffer(&data);
	glfwSetKeyCallback(data.win_ptr, key_callback);
	while (!glfwWindowShouldClose (data.win_ptr))
		draw(&data);
	glfwTerminate();
	return (0);
}