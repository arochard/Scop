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

static void		readV(FILE *fp, t_data *data)
{
	size_t		buffer;
	char		*linePtr;
	int 		flag;

	flag = 0;
	buffer = 128;
	while (flag == 0 && getline(&linePtr, &buffer, fp) > 0)
	{
		if (linePtr[0] == 'v')
			fillTab(linePtr, data);
		if (linePtr[0] == 'f')
			flag = 1;
	}
}

static int		readNbVLine(FILE *fp)
{
	size_t		buffer;
	char		*linePtr;
	int			countLine;
	int 		flag;

	countLine = 0;
	flag = 0;
	buffer = 128;
	while (flag == 0 && getline(&linePtr, &buffer, fp) > 0)
	{
		if (linePtr[0] == 'v')
			countLine++;
		if (linePtr[0] == 'f')
			flag = 1;
	}
	rewind(fp);
	return (countLine);
}

void			parserObj(t_data *data)
{
	FILE		*fp;
	int			sizeTab;

	fp = fopen(data->fileObj, "r");
	if (fp == NULL)
	{
		printf("Error read obj file\n");
		exit(0);
	}
	sizeTab = readNbVLine(fp);
	printf("Nb line: %d\n", sizeTab);
	data->pointsTab = (float*) malloc(sizeof(float) * (sizeTab * 3));
	fclose(fp);
	fp = fopen(data->fileObj, "r");
	readV(fp, data);
	fclose(fp);

	// //tmp
	//  int i = 0;

	// while (data->pointsTab[i])
	// {
	// 	printf("Tab[%f]\n", data->pointsTab[i]);
	// 	i++;
	// }
}