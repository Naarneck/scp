#include "scop.h"

void shader_init(char *filename, t_shader *shader)
{
	unsigned int i;

	shader->program = glCreateProgram();
	shader->shaders[0] = shader_create(shader_load(ft_strjoin(filename, ".vs")), GL_VERTEX_SHADER);
	shader->shaders[1] = shader_create(shader_load(ft_strjoin(filename, ".fs")), GL_FRAGMENT_SHADER);
	i = 0;
	while (i < NUM_SHADERS)
	{
		glAttachShader(shader->program, shader->shaders[i]);
		i++;
	}
	
	glBindAttribLocation(shader->program, 0, "position");
	glBindAttribLocation(shader->program, 1, "texCoord");

	glLinkProgram(shader->program);
	//Checkshader;
	glValidateProgram(shader->program);
	//Checkshader;
	shader->unifs[TRANSFORM_U] = glGetUniformLocation(shader->program, "transform");
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
	const GLchar 	*shaderSrc;
	GLint			shaderSrcLength[1];	

	shader = glCreateShader(shaderType);
	if (!shader)
		printf("error create shader\n");
	shaderSrc = text;
	// shaderSrcLength[0] = ft_strlen(text);
	glShaderSource(shader, 1, &shaderSrc, NULL);
	glCompileShader(shader);
	//checkshader;
	return shader;
}

void	shader_bind(t_shader *shader)
{
	glUseProgram(shader->program);
}

void	shader_update(t_transf *transf, t_shader *shader, t_cam *camera)
{
	t_mat4 model = mat4_mult(cam_getViewProj(camera), transform_getModel(transf));
	glUniformMatrix4fv(shader->unifs[TRANSFORM_U], 1, GL_FALSE /*transpose*/, &model.a[0][0]);
}

char *shader_load(const char *filename)
{
	int fd;
	char *text;
	char *line;

	text = ft_strnew(1);
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		line = ft_strjoin(line, "\n");
		text = ft_strjoin(text, line);
		free(line);
	}
	// printf("%s\n", text);
	close(fd);
	return text;
}
