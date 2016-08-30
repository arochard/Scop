#include "../includes/scop.h"

static void		fillTab(char *line, t_data *data)
{
	char		letter;
	int			read;
	static int	index = 0;

	read = sscanf(line, "%c %f %f %f", &letter, &(data->pointsTab[index]), &(data->pointsTab[index + 1]), &(data->pointsTab[index + 2]));
	index += 3;
	if (read != 4 && letter != 'v')
	{
		printf("Error read: v format\n");
		exit(0);
	}
}

static void		read(FILE *fp, t_data *data, char del)
{
	size_t		buffer;
	char		*linePtr;
	int 		flag;

	flag = 0;
	buffer = 128;
	while (flag == 0 && getline(&linePtr, &buffer, fp) > 0)
	{
		if (del == 'v' linePtr[0] == del)
			fillTabV(linePtr, data);
		if (del == 'f' && linePtr[0] == del)
			fillTabF(linePtr);
	}
}

static int		readNbLine(FILE *fp, char del)
{
	size_t		buffer;
	char		*linePtr;
	int			countLine;

	countLine = 0;
	buffer = 128;
	while (getline(&linePtr, &buffer, fp) > 0)
	{
		if (linePtr[0] == del)
			countLine++;
	}
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
	data->size_tab = (readNbLine(floatp, 'v') * 3);
	printf("Nb line: %d\n", data->size_tab);
	data->pointsTab = (float*) malloc(sizeof(float) * data->size_tab);
	fclose(fp);
	fp = fopen(data->fileObj, "r");
	readV(fp, data);
	fclose(fp);

	printf("OUHOOUH\n");
}