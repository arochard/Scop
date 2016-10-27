#include "../includes/scop.h"

static void			fillTab(t_data *data, int x, GLfloat color)
{
	static int		index = 0;

	data->final_buffer_tab[index] = data->vertex_tab[(x * 3) - 3];
	data->final_buffer_tab[index+1] = data->vertex_tab[(x * 3) - 2];
	data->final_buffer_tab[index+2] = data->vertex_tab[(x * 3) - 1];
	data->final_buffer_tab[index+3] = color;
	data->final_buffer_tab[index+4] = color;
	data->final_buffer_tab[index+5] = color;
	index += 6;
}

static void			final_buffer(char *line, t_data *data)
{
	char			letter;
	int				read[4];
	int				rdn;
	GLfloat			color[5] = {0.827f, 0.753f, 0.663f, 0.502f, 0.412f};
	static int 		index_color = 0;

	if (index_color == 4)
		index_color = 0;
	rdn = sscanf(line, "%c %d %d %d %d", &letter, &read[0], &read[1], &read[2], &read[3]);
	if (rdn < 4 || letter != 'f')
	{
		printf("Error read: v format\n");
		exit(0);
	}
	fillTab(data, read[0], color[index_color]);
	fillTab(data, read[1], color[index_color]);
	fillTab(data, read[2], color[index_color]);
	if (rdn == 5 && letter == 'f')
	{
		fillTab(data, read[0], color[index_color]);
		fillTab(data, read[2], color[index_color]);
		fillTab(data, read[3], color[index_color]);
	}
	index_color++;
		
}

static void			fillTabV(char *line, t_data *data)
{
	char			letter;
	int				read;
	static int		index = 0;
	
	data->x[0] = 0.0f;
	data->x[1] = 0.0f;
	data->y[0] = 0.0f;
	data->y[1] = 0.0f;
	read = sscanf(line, "%c %f %f %f", &letter, &(data->vertex_tab[index]), &(data->vertex_tab[index + 1]), &(data->vertex_tab[index + 2]));
	if (data->vertex_tab[index] < data->x[0])
		data->x[0] = data->vertex_tab[index];
	if (data->vertex_tab[index] > data->x[1])
		data->x[1] = data->vertex_tab[index];
	if (data->vertex_tab[index + 1] < data->y[0])
		data->y[0] = data->vertex_tab[index + 1];
	if (data->vertex_tab[index + 1] > data->y[1])
		data->y[1] = data->vertex_tab[index + 1];
	index += 3;
	if (read != 4 || letter != 'v')
	{
		printf("Error read: v format\n");
		exit(0);
	}
}

static void			read(FILE *fp, t_data *data)
{
	size_t			buffer;
	char			*linePtr;
	int 			flag;

	flag = 0;
	buffer = 256;
	while (flag == 0 && getline(&linePtr, &buffer, fp) > 0)
	{
		if (linePtr[0] == 'v')
			fillTabV(linePtr, data);
		if (linePtr[0] == 'f')
			final_buffer(linePtr, data);
	}
}

static int			readNbLine(FILE *fp, char del)
{
	size_t			buffer;
	char			*linePtr;
	int				countLine;
	int				read[5];
	char			letter;

	countLine = 0;
	buffer = 128;
	while (getline(&linePtr, &buffer, fp) > 0)
	{
		if (del == 'v' && linePtr[0] == del)
			countLine++;
		if (del == 'f' && linePtr[0] == del)
		{
			read[0] = sscanf(linePtr, "%c %d %d %d %d", &letter, &read[1], &read[2], &read[3], &read[4]);
			if (read[0] == 4 && letter == 'f')
				countLine++;
			else if (read[0] == 5 && letter == 'f')
				countLine += 2;
		}
	}
	rewind(fp);
	return (countLine);
}

void				parserObj(t_data *data)
{
	FILE			*fp;

	fp = fopen(data->fileObj, "r");
	if (fp == NULL)
	{
		printf("Error read obj file\n");
		exit(0);
	}
	data->size_tab_vertex = readNbLine(fp, 'v') * 3;
	data->size_tab_indice = readNbLine(fp, 'f') * 18;
	data->vertex_tab = (float*) malloc(sizeof(float) * data->size_tab_vertex);
	data->final_buffer_tab = (GLfloat*) malloc(sizeof(GLfloat) * data->size_tab_indice);
	fclose(fp);
	fp = fopen(data->fileObj, "r");
	read(fp, data);
	fclose(fp);
	scaleRange(data);
}