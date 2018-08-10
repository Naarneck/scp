#include "scop.h"
#include "stb_image.h"

void	texture_init(const char *fileName, t_texture *texture)
{
	int width;
	int height;
	int nComp;

	unsigned char * data;
	data = stbi_load(fileName, &width, &height, &nComp, 4);
	if (data == NULL)
		printf("error: image data texture\n");
	glGenTextures(1, &texture->texture);
	glBindTexture(GL_TEXTURE_2D, texture->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	write(1,"aa\n",3);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);

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
