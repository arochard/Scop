#include "../includes/scop.h"

static void			fillTabF(char *line, t_data *data)
{
	char			letter;
	unsigned short	read[2];
	static int		index = 0;

	read[0] = sscanf(line, "%c %hd %hd %hd %hd", &letter, &(data->indice_tab[index]), &(data->indice_tab[index + 1]), &(data->indice_tab[index + 2]), &read[1]);
	index += 3;
	if (read[0] < 4 || letter != 'f')
	{
		printf("Error read: v format\n");
		exit(0);
	}
	else if (read[0] == 5 && letter == 'f')
	{
		data->indice_tab[index] = data->indice_tab[index - 3];
		data->indice_tab[index + 1] = data->indice_tab[index - 1];
		data->indice_tab[index + 2] = read[1];
		index += 3;
	}
}

static void		fillTabV(char *line, t_data *data)
{
	char		letter;
	int			read;
	static int	index = 0;

	read = sscanf(line, "%c %f %f %f", &letter, &(data->vertex_tab[index]), &(data->vertex_tab[index + 1]), &(data->vertex_tab[index + 2]));
	index += 3;
	if (read != 4 || letter != 'v')
	{
		printf("Error read: v format\n");
		exit(0);
	}
}

static void		read(FILE *fp, t_data *data)
{
	size_t		buffer;
	char		*linePtr;
	int 		flag;

	flag = 0;
	buffer = 256;
	while (flag == 0 && getline(&linePtr, &buffer, fp) > 0)
	{
		if (linePtr[0] == 'v')
			fillTabV(linePtr, data);
		if (linePtr[0] == 'f')
			fillTabF(linePtr, data);
	}
}

static int		readNbLine(FILE *fp, char del)
{
	size_t		buffer;
	char		*linePtr;
	int			countLine;
	int			read[5];
	char		letter;

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
	printf("count line%d\n", countLine);
	return (countLine);
}

void			parserObj(t_data *data)
{
	FILE		*fp;

	fp = fopen(data->fileObj, "r");
	if (fp == NULL)
	{
		printf("Error read obj file\n");
		exit(0);
	}
	data->size_tab_vertex = readNbLine(fp, 'v') * 3;
	data->size_tab_indice = readNbLine(fp, 'f') * 3;
	printf("size vertex: %d\n", data->size_tab_vertex);
	printf("size indice: %d\n", data->size_tab_indice);
	data->vertex_tab = (float*) malloc(sizeof(float) * data->size_tab_vertex);
	data->indice_tab = (GLushort*) malloc(sizeof(GLushort) * data->size_tab_indice);
	fclose(fp);
	fp = fopen(data->fileObj, "r");
	read(fp, data);
	fclose(fp);
	scaleRange(data);
	int i = 0;
	while (data->vertex_tab[i])
	{
		printf("%f\n", data->vertex_tab[i]);
		i++;
	}
}