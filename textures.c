#include "scop.h"
#include "stb_image.h"

unsigned char		*load_bmp(const char *filename, unsigned int *width, unsigned int *height)
{
	unsigned char		header[54];
	unsigned int		datapos;
	unsigned int		size;
	unsigned char		*data;
	FILE				*file;

	file = fopen(filename, "rb");
	if (!file)
		return (NULL);
	if (fread(header, 1, 54, file) != 54)
		return (NULL);
	if (header[0] != 'B' || header[1] != 'M')
		return (NULL);
	datapos = *(int*)&(header[0x0A]);
	size = *(int*)&(header[0x22]);
	*width = *(int*)&(header[0x12]);
	*height = *(int*)&(header[0x16]);
	if (size == 0)
		size = (*width) * (*height) * 3;
	if (datapos == 0)
		datapos = 54;
	data = malloc(sizeof(unsigned char) * size);
	fread(data, 1, size, file);
	return (data);
}

void	texture_init(const char *filename, t_texture *texture)
{
	unsigned int width;
	unsigned int height;
	int nComp;

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
	// write(1,"aa\n",3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	// stbi_image_free(data);
	free (data);
}

void	texture_bind(unsigned int unit, t_texture *texture)
{
	// if (unit <= 31 && unit >=0)
	// {
	// 	printf("error: unit texture\n");
	// 	exit(0);
	// }
	glActiveTexture(GL_TEXTURE0 + unit);
	glUniform1i(GL_TEXTURE0, 0);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
}

void	texture_del(t_texture *texture)
{
	glDeleteTextures(1, &texture->texture);
}
