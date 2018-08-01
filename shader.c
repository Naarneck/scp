#include "scop.h"

void shader_init(char *filename, t_shader *shader)
{
	unsigned int i;

	shader->program = glCreateProgram();
	shader->shaders[0] = shader_create(shader_load(ft_strjoin(filename, ".vs")), GL_VERTEX_SHADER);
	write(1, "ok\n" ,3);
	shader->shaders[1] = shader_create(shader_load(ft_strjoin(filename, ".fs")), GL_FRAGMENT_SHADER);
	i = 0;
	while (i < NUM_SHADERS)
	{
		glAttachShader(shader->program, shader->shaders[i]);
		i++;
	}
	
	glBindAttribLocation(shader->program, 0, "position");
	glLinkProgram(shader->program);
	//Checkshader;
	glValidateProgram(shader->program);
	//Checkshader;
}

void shader_del(t_shader *shader)
{
	unsigned int i;
	
	i = 0;
	while (i < NUM_SHADERS)
	{
		glDetachShader(shader->program, shader->shaders[i]);
		glDeleteShader(shader->shaders[i]);
		i++;
	}
	glDeleteProgram(shader->program);
}


GLuint shader_create(char *text, GLenum shaderType)
{
	GLuint			shader;
	const GLchar 	*shaderSrc[1];
	GLint			shaderSrcLength[1];	

	shader = glCreateShader(shaderType);
	if (!shader)
		printf("error create shader\n");
	shaderSrc[0] = text;
	shaderSrcLength[0] = ft_strlen(text);
		write(1, "sk\n" ,3);
	glShaderSource(shader, 1, (const char**)&text, shaderSrcLength);
		write(1, "nk\n" ,3);
	glCompileShader(shader);
	//checkshader;
	return shader;
}

void shader_bind(t_shader *shader)
{
	glUseProgram(shader->program);
}

char *shader_load(const char *filename)
{
	int fd;
	char *text;
	char *line;

	text = ft_strnew(1);
	write(1, "ak\n" ,3);
	fd = open(filename, O_RDONLY);
		if (fd < 0)
			exit(0);
	while (get_next_line(fd, &line) == 1)
	{
		line = ft_strjoin(line, "\n");
		text = ft_strjoin(text, line);
		free(line);
	}
	printf("%s\n", text);
	close(fd);
	return text;
}
