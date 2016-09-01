#include "../includes/scop.h"


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
	parserObj(&data);
	init_window(&data);
	loading_buffer(&data);
	while (!glfwWindowShouldClose (data.win_ptr))
		draw(&data);
	glfwTerminate();
	return (0);
}