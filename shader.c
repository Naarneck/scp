#include "scop.h"

void shader_init(char *filename, t_shader *shader)
{
	unsigned int i;

	shader->program = glCreateProgram();
	shader->shaders[0] = shader_create(shader_load("shaders/basic.vs"), GL_VERTEX_SHADER);
	shader->shaders[1] = shader_create(shader_load("shaders/basic.fs"), GL_FRAGMENT_SHADER);
	i = 0;
	while (i < NUM_SHADERS)
	{
		glAttachShader(shader->program, shader->shaders[i]);
		i++;
	}
	
	glBindAttribLocation(shader->program, 0, "position");
	glBindAttribLocation(shader->program, 1, "texCoord");
	glBindAttribLocation(shader->program, 2, "normal");

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
	free(text);
	return shader;
}

void	shader_bind(t_shader *shader)
{
	glUseProgram(shader->program);
}

void	shader_update(t_transf *transf, t_shader *shader, t_cam *cam)
{
	// t_mat4 model = mat4_mult(mat4_identity(), transform_getModel(transf));
	t_mat4 model = transform_getModel(transf);
	t_mat4 view = cam_lookAt(cam->pos, vadd(cam->pos, cam->forward), cam->up);
	t_mat4 projection = cam->perspective;
	t_mat4 mvp = mat4_mult(model, mat4_mult(view, projection));
	// t_mat4 mvp = mat4_mult(model, projection);
	// t_mat4 mvp = mat4_mult(view, model);

	// t_mat4 model = mat4_mult(cam_getViewProj(camera), transform_getModel(transf));
	// t_mat4 model = transform_getModel(transf);
	// glMatrixMode(GL_MODELVIEW);

	glUniformMatrix4fv(shader->unifs[TRANSFORM_U], 1, GL_FALSE /*transpose*/, &mvp.a[0][0]);
}

char	*shader_load(const char *filename)
{
	int fd;
	char *text;
	char *line;

	text = ft_strnew(100000);
	fd = open(filename, O_RDONLY);
	printf("fd # %d\n", fd);
	while (get_next_line(fd, &line) == 1)
	{
		ft_strcat(text, "\n");
		ft_strcat(text, line);
		free(line);
	}
	return (text);
}
