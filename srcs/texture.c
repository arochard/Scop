/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arochard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 20:41:28 by arochard          #+#    #+#             */
/*   Updated: 2016/10/31 20:41:29 by arochard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scop.h"
#include <errno.h>

static GLuint	create_texture(t_bmp *bmp)
{
	GLuint		texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmp->width,
		bmp->height, 0, GL_BGR, GL_UNSIGNED_BYTE, bmp->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return (texture);
}

GLuint			load_bmp(const char *path)
{
	t_bmp		bmp;

	bmp.fp = fopen(path, "rb");
	if (bmp.fp == NULL)
	{
		printf("%s : Error BMP file: %s\n", path, strerror(errno));
		return (0);
	}
	if ((fread(bmp.header, 1, 54, bmp.fp) != 54) ||
		(bmp.header[0] != 'B' || bmp.header[1] != 'M'))
	{
		printf("Not correct bmp file\n");
		return (0);
	}
	bmp.data_pos = *(int*)&(bmp.header[0x0A]);
	bmp.img_size = *(int*)&(bmp.header[0x22]);
	bmp.width = *(int*)&(bmp.header[0x12]);
	bmp.height = *(int*)&(bmp.header[0x16]);
	if (bmp.img_size == 0)
		bmp.img_size = bmp.width * bmp.height * 3;
	if (bmp.data_pos == 0)
		bmp.data_pos = 54;
	bmp.data = (char*)malloc(sizeof(char) * bmp.img_size);
	fread(bmp.data, 1, bmp.img_size, bmp.fp);
	fclose(bmp.fp);
	return (create_texture(&bmp));
}
