#include "../includes/scop.h"
#include <errno.h>

static GLuint	create_texture(t_bmp *bmp)
{
	GLuint		texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, bmp->width, bmp->height, 0, GL_BGR, GL_UNSIGNED_BYTE, bmp->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return(texture);
}

GLuint			load_bmp(const char *path)
{
	t_bmp		bmp;

	bmp.fp = fopen(path, "rb");
	if (bmp.fp == NULL)
	{
		printf("%s : Error BMP file: %s\n", path, strerror(errno));
		return(0);
	}
	if (fread(bmp.header, 1, 54, bmp.fp) != 54)
	{
		printf("Not correct bmp file\n");
		return (0);
	}
	if (bmp.header[0] != 'B' || bmp.header[1] != 'M')
	{
		printf("Not correct bmp file\n");
		return (0);
	}
	bmp.dataPos = *(int*) & (bmp.header[0x0A]);
	bmp.imgSize = *(int*) & (bmp.header[0x22]);
	bmp.width = *(int*) & (bmp.header[0x12]);
	bmp.height = *(int*) & (bmp.header[0x16]);
	if (bmp.imgSize == 0)
		bmp.imgSize = bmp.width * bmp.height * 3;
	if (bmp.dataPos == 0)
		bmp.dataPos = 54;
	bmp.data = (char*)malloc(sizeof(char) * bmp.imgSize);
	fread(bmp.data, 1, bmp.imgSize, bmp.fp);	
	fclose(bmp.fp);
	return (create_texture(&bmp));
}