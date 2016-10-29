#include "../includes/scop.h"

GLfloat				g_modelMatrix[16] = 		{1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 2.0f, 1.0};
int 				g_is_texture = 0;

int			main(int argc, char **argv)
{
	
	t_data		data;

	data.width = 1920;
	data.height = 1080;
	data.ratio = data.width / data.height;
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
	parserObj(&data);
	init_window(&data);
	loading_buffer(&data);
	glfwSetKeyCallback(data.win_ptr, key_callback);
	while (!glfwWindowShouldClose (data.win_ptr))
		draw(&data);
	glfwTerminate();
	return (0);
}