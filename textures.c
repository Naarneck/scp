/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:28:11 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/17 19:28:12 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

unsigned char	*load_bmp(const char *filename, unsigned int *width, unsigned int *height)
{
	FILE				*file;
	unsigned char		info[54];
	unsigned char		*data;
	unsigned int		start;
	unsigned int		size;

	file = fopen(filename, "rb");
	if (!file)
		return (NULL);
	if (fread(info, 1, 54, file) != 54)
		return (NULL);
	if (info[0] != 'B' || info[1] != 'M')
		return (NULL);
	start = *(unsigned int*)&(info[0x0A]);
	size = *(unsigned int*)&(info[0x22]);
	*width = *(unsigned int*)&(info[0x12]);
	*height = *(unsigned int*)&(info[0x16]);
	if (!size)
		size = (*width) * (*height) * 3;
	if (!start)
		start = 54;
	data = (unsigned char *)malloc(sizeof(unsigned char) * size);
	fread(data, 1, size, file);
	return (data);
}

void			texture_init(const char *filename, t_texture *texture)
{
	unsigned int width;
	unsigned int height;

	unsigned char * data;
	data = load_bmp(filename, &width, &height);
	if (data == NULL)
		printf("error: image data texture\n");
	glGenTextures(1, &texture->texture);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	free (data);
}

void			texture_bind(unsigned int unit, t_texture *texture)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glUniform1i(GL_TEXTURE0, 0);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
}

void			texture_del(t_texture *texture)
{
	glDeleteTextures(1, &texture->texture);
}
