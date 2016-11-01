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

static GLuint	create_texture(t_bmp *b)
{
	GLuint		texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, b->width,
		b->height, 0, GL_BGR, GL_UNSIGNED_BYTE, b->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return (texture);
}

GLuint			load_bmp(const char *path)
{
	t_bmp		b;

	b.fp = fopen(path, "rb");
	if (b.fp == NULL)
	{
		printf("%s : Error bmp file: %s\n", path, strerror(errno));
		return (0);
	}
	if ((fread(b.header, 1, 54, b.fp) != 54) ||
		(b.header[0] != 'B' || b.header[1] != 'M'))
	{
		printf("Not correct b file\n");
		return (0);
	}
	b.data_pos = *(int*)&(b.header[0x0A]);
	b.img_size = *(int*)&(b.header[0x22]);
	b.width = *(int*)&(b.header[0x12]);
	b.height = *(int*)&(b.header[0x16]);
	b.img_size = (b.img_size == 0) ? b.width * b.height * 3 : b.img_size;
	b.data_pos = (b.data_pos == 0) ? 54 : b.data_pos;
	b.data = (char*)malloc(sizeof(char) * b.img_size);
	fread(b.data, 1, b.img_size, b.fp);
	fclose(b.fp);
	return (create_texture(&b));
}
