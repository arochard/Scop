#include "../includes/scop.h"


int			main(int argc, char **argv)
{
	t_data		*data = (t_data *)malloc(sizeof(t_data));

	if (argc == 3)
	{
		data->fileObj = argv[1];
		data->fileMtl = argv[2];
	}
	else
	{
		printf("Usage: ./Scop [obj file] [mtl file]");
		exit(0);
	}

	parserObj(data);
	init_window(data);

	return (0);
}