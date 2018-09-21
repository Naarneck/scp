/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izelensk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 19:20:49 by izelensk          #+#    #+#             */
/*   Updated: 2018/09/17 19:20:55 by izelensk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <GL/glew.h>
# include <OpenGL/gl.h>
# include <SDL2/SDL.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <sys/time.h>

# define WIDTH 1200
# define HEIGHT 800
# define NUM_BUFFERS 3

# define NORMAL_VB 2
# define TEXCOORD_VB 1
# define POSITION_VB 0

# define NUM_SHADERS 2

# define NUM_UNIFORMS 3
# define TRANSFORM_U 0
# define MODE_U 1
# define LOOP_U 2

# define PI 3.14159265
# define COSN(angle) cos(angle * PI / 180)
# define SINS(angle) sin(angle * PI / 180)
# define TANG(angle) tan(angle * PI / 180)
# define ACOSN(angle) acos(angle) * 180 / PI
# define TORADS(angle) (angle * PI / 180.0f)

typedef	struct	s_color
{
	float		r;
	float		g;
	float		b;
}				t_color;

typedef	struct	s_vector
{
	float		x;
	float		y;
	float		z;
}				t_vector;

typedef	struct	s_coord
{
	float		x;
	float		y;
}				t_coord;

typedef	struct	s_mat4
{
	float		a[4][4];
}				t_mat4;

typedef	struct	s_objindex
{
	t_vector		*v;
	t_coord			*vt;
	t_vector		*vn;
	t_vector		*normals;
	unsigned int	*posid;
	unsigned int	*uvsid;
	unsigned int	*normalsid;

	unsigned int	numindices;
	unsigned int	numtex;
	unsigned int	numnormals;
	unsigned int	numpositions;
	unsigned int	is_uvs;
	unsigned int	is_normals;
	float			far;
	int				status;
}				t_objindex;

typedef	struct	s_mesh
{
	t_vector		*positions;
	t_coord			*uvs;
	t_vector		*normals;

	unsigned int	numvert;
	GLuint			vertexarrobj;
	GLuint			vertexarrbuf[NUM_BUFFERS];
	unsigned int	drawcount;

}				t_mesh;

typedef	struct	s_shader
{
	GLuint			program;
	GLuint			shaders[NUM_SHADERS];
	GLuint			unifs[NUM_UNIFORMS];
}				t_shader;

typedef	struct	s_texture
{
	GLuint			texture;
	int				id;
	char			*name;
}				t_texture;

typedef	struct	s_cam
{
	t_mat4		perspective;
	float		fov;
	float		aspect;
	t_vector	pos;
	t_vector	forward;
	t_vector	up;
}				t_cam;

typedef	struct	s_model
{
	t_mat4		pos;
	t_mat4		rot;
	t_mat4		rotx;
	t_mat4		roty;
	t_mat4		rotz;
	t_mat4		scale;
}				t_model;

typedef	struct	s_fileobj
{
	char	*line;
	char	**line_arr;
	int		i;
	int		num;
	int		fd;
}				t_fileobj;

typedef	struct	s_transf
{
	t_vector	pos;
	t_vector	rot;
	t_vector	scale;
	int			mode;
	float		loop;
}				t_transf;

typedef	struct	s_data
{
	SDL_Window		*window;
	SDL_GLContext	glcontext;
	GLenum			status;
	int				run;
	t_mesh			mesh;
	t_shader		shader;
	t_texture		texture;
	t_transf		transform;
	t_cam			camera;
	t_objindex		obji;
}				t_data;

int				getuv(char *str);
int				getnormal(char *str);
char			**ft_strsplitnum(char const *s, char c, int *num);
float			ft_atof(char *str);

void			obj_init(t_objindex *obji, const char *fn);
int				obj_alloc(t_objindex *obji);
void			obj_free_line(t_fileobj *fo);
void			obj_checkfile(const char *filename, t_objindex *obji);
void			obj_triangulate_faces(t_objindex *obji, t_fileobj *fo);
void			obj_write_v_vt_vn(t_objindex *obji, t_fileobj *fo, int id);
void			obj_loadfile(const char *filename, t_objindex *obji);

void			transform_init(t_vector pos, t_vector rot,
												t_vector scale, t_transf *tf);
t_mat4			transform_getmodel(t_transf *tf);

void			cam_init(t_vector pos, float fov, float aspect, t_cam *cam);
t_mat4			cam_lookat(t_vector pos, t_vector dir, t_vector up);
t_mat4			cam_perspective(float fov, float aspect,
													float znear, float zfar);

void			shader_init(t_shader *shader);
void			shader_del(t_shader *shader);
GLuint			shader_create(char *text, GLenum shadertype);
void			shader_bind(t_shader *shader);
void			shader_update(t_transf *transf, t_shader *shader, t_cam *cam);
void			shader_mode_update(t_shader *shader, t_transf *tf);
char			*shader_load(const char *filename);

void			mesh_init(t_mesh *mesh, t_objindex *obji);
void			mesh_del(t_mesh *mesh);
void			mesh_draw(t_mesh *mesh);
void			mesh_index_obj(t_mesh *mesh, t_objindex *obji);

void			texture_del(t_texture *texture);
void			texture_bind(unsigned int unit, t_texture *texture);
void			texture_init(const char *filename, t_texture *texture);

t_vector		vinit(float x, float y, float z);
t_vector		vsub(t_vector v1, t_vector v2);
t_vector		vadd(t_vector v1, t_vector v2);
t_vector		vmul(t_vector v1, float l);
float			vlen(t_vector v1);
t_vector		vnorm(t_vector v1);
float			vdot(t_vector v1, t_vector v2);
t_vector		vcross(t_vector v1, t_vector v2);
t_vector		vcalcnormal(t_vector p0, t_vector p1, t_vector p2);
float			vmax(t_vector vec);

t_mat4			mat4_scale(t_vector sc);
t_mat4			mat4_rotatex(float ang);
t_mat4			mat4_rotatey(float ang);
t_mat4			mat4_rotatez(float ang);
t_mat4			mat4_translate(t_vector pos);
t_mat4			mat4_mult(t_mat4 a, t_mat4 b);
t_mat4			mat4_transpose(t_mat4 src);
t_mat4			mat4_identity(void);

t_coord			cinit(float x, float y);
t_coord			cmul(t_coord v1, float l);
t_coord			cnorm(t_coord v1);
float			cdot(t_coord v1, t_coord v2);
float			clen(t_coord v1);

void			quit_scop(t_data *d);
void			handle_event_tex(SDL_Event event, t_transf *tf,
															t_texture *tex);
void			handle_event_obj(SDL_Event event, t_transf *tf);
int				handle_event(SDL_Event event, t_transf *tf,
												t_cam *cam, t_texture *tex);
void			sdlgl_init(t_data *d);
void			data_init(t_data *d);
void			data_del(t_data *d);
int				print_usage(void);
#endif
