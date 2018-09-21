/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:25:49 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/17 19:25:52 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	shader_init(t_shader *shader)
{
	shader->program = glCreateProgram();
	shader->shaders[0] = shader_create(shader_load("shaders/basic.vs"),
															GL_VERTEX_SHADER);
	shader->shaders[1] = shader_create(shader_load("shaders/basic.fs"),
															GL_FRAGMENT_SHADER);
	glAttachShader(shader->program, shader->shaders[0]);
	glAttachShader(shader->program, shader->shaders[1]);
	glBindAttribLocation(shader->program, 0, "position");
	glBindAttribLocation(shader->program, 1, "texCoord");
	glBindAttribLocation(shader->program, 2, "normal");
	glLinkProgram(shader->program);
	glValidateProgram(shader->program);
	shader->unifs[TRANSFORM_U] = glGetUniformLocation(shader->program,
																"transform");
	shader->unifs[MODE_U] = glGetUniformLocation(shader->program, "mode");
	shader->unifs[LOOP_U] = glGetUniformLocation(shader->program, "loop");
}

void	shader_del(t_shader *shader)
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

GLuint	shader_create(char *text, GLenum shadertype)
{
	GLuint			shader;
	const GLchar	*shadersrc;

	shader = glCreateShader(shadertype);
	if (!shader)
		printf("error create shader\n");
	shadersrc = text;
	glShaderSource(shader, 1, &shadersrc, NULL);
	glCompileShader(shader);
	free(text);
	return (shader);
}

void	shader_bind(t_shader *shader)
{
	glUseProgram(shader->program);
}

void	shader_update(t_transf *transf, t_shader *shader, t_cam *cam)
{
	t_mat4	model;
	t_mat4	view;
	t_mat4	projection;
	t_mat4	mvp;

	model = transform_getmodel(transf);
	view = cam_lookat(cam->pos, vadd(cam->pos, cam->forward), cam->up);
	projection = cam->perspective;
	mvp = mat4_mult(model, mat4_mult(view, projection));
	transf->loop += 0.05f;
	glUniformMatrix4fv(shader->unifs[TRANSFORM_U], 1, GL_FALSE, &mvp.a[0][0]);
}
