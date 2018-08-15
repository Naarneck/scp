#ifndef SCOP_H
# define SCOP_H

# include <stdio.h> //del
# include <math.h>
# include <stdlib.h>
# include <GL/glew.h> 
# include <OpenGL/gl.h>
# include <SDL2/SDL.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800
# define NUM_BUFFERS 3
# define INDEX_VB 2
# define TEXCOORD_VB 1
# define POSITION_VB 0
 
# define NUM_SHADERS 2

# define NUM_UNIFORMS 1
# define TRANSFORM_U 0

# define PI 3.14159265
# define COSN(angle) cos(angle * PI / 180)
# define SINS(angle) sin(angle * PI / 180)
# define TANG(angle) tan(angle * PI / 180)
# define ACOSN(angle) acos(angle) * 180 / PI

# define KEY_UP 13
# define KEY_DOWN 1
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define KEY_AUP 126
# define KEY_ADOWN 125
# define KEY_ALEFT 123
# define KEY_ARIGHT 124
# define KEY_ESC 53
# define KEY_SPACE 49
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SHIFT 257
# define KEY_CTRL 256
# define KEY_RSHIFT 258
# define KEY_RCTRL 269
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_Q 12
# define KEY_E 14

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
	float		a[4][4]; //wtf 
}				t_mat4;

typedef	struct	s_vertex
{
	t_vector	pos;
	t_coord		uv;
}				t_vertex;

typedef	struct	s_objIndex
{
	t_vector		*positions;
	t_vector		*texCoords;
	t_vertex		*vertices; //test
	t_vector		*normals;
	unsigned int	*indices;
	unsigned int	numIndices;
	unsigned int	numTex;
	unsigned int	numNormals;
	unsigned int	numPositions;
	unsigned int	numLines;
	char			*text;
}				t_objIndex;

typedef	struct	s_mesh
{
	t_vertex*		vertices;
	unsigned int	numVert;
	GLuint			vertexArrObj;
	GLuint			vertexArrBuf[NUM_BUFFERS];
	unsigned int	drawCount;

}				t_mesh;

typedef	struct	s_shader
{
	GLuint			program;
	GLuint			shaders[NUM_SHADERS];
	GLuint			unifs[NUM_UNIFORMS];
}				t_shader;

typedef	struct	s_data
{
	SDL_Window		*window;
	SDL_GLContext	glContext;
	GLenum			status;
	int				run;

}				t_data;

typedef	struct	s_texture
{
	GLuint			texture;
}				t_texture;

typedef	struct	s_cam
{
	t_mat4		perspective;
	// float		zNear;
	// float		zNear;
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
	t_mat4		rotX;
	t_mat4		rotY;
	t_mat4		rotZ;
	t_mat4		scale;
}				t_model;

typedef	struct	s_transf
{
	t_vector	pos;
	t_vector	rot;
	t_vector	scale;
}				t_transf;

void			obj_checkFile(const char *filename, t_objIndex *obji);
void			obj_loadFile(const char *filename, t_objIndex *obji);

void			transform_init(t_vector pos, t_vector rot, t_vector scale, t_transf *tf);
t_mat4			transform_getModel(t_transf *tf);

void			cam_init(t_vector pos, float fov, float aspect, t_cam *cam);
t_mat4			cam_getViewProj(t_cam *cam);
t_mat4			cam_lookAt(t_vector pos, t_vector dir, t_vector up);
t_mat4			cam_perspective(float fov, float aspect, float zNear, float zFar);

void			shader_init(char *filename, t_shader *shader);
void			shader_del(t_shader *shader);
GLuint			shader_create(char *text, GLenum shaderType);
void			shader_bind(t_shader *shader);
char			*shader_load(const char *filename);
void			shader_update(t_transf *transf, t_shader *shader, t_cam *cam);
void 			mesh_init(t_vertex *vertices, unsigned int numVerices, unsigned int *indices, unsigned int numIndices, t_mesh *mesh);
// void			mesh_init(t_vertex *vertices, unsigned int num, t_mesh * mesh);
void			mesh_del(t_mesh *mesh);
void			mesh_draw(t_mesh *mesh);

void			texture_del(t_texture *texture);
void			texture_bind(unsigned int unit, t_texture *texture);
void			texture_init(const char *fileName, t_texture *texture);

t_color			col_mix(t_color base, t_color col2);
t_color			col_mult_d(t_color col1, float d);
t_color			col_mult(t_color col1, t_color col2);
t_color			col_norm(int col);
t_color			col_avg(t_color col1, t_color col2);
t_color			col_clamp(t_color col1);
t_color			col_add(t_color col1, t_color col2);

t_vector		vinit(float x, float y, float z);
t_vector		vsub(t_vector v1, t_vector v2);
t_vector		vadd(t_vector v1, t_vector v2);
t_vector		vmul(t_vector v1, float l);
float			vlen(t_vector v1);
t_vector		vnorm(t_vector v1);
float			vdot(t_vector v1, t_vector v2);
t_vector		vcross(t_vector v1, t_vector v2);

t_mat4			mat4_scale(t_vector sc);
t_mat4			mat4_rotateX(float ang);
t_mat4			mat4_rotateY(float ang);
t_mat4			mat4_rotateZ(float ang);
t_mat4			mat4_translate(t_vector pos);
t_mat4 			mat4_mult(t_mat4 a, t_mat4 b);
t_mat4			mat4_transpose(t_mat4 src);

t_vertex		vertex_init(t_vector pos, t_coord uv);
t_coord			vertex_getUV(t_vertex vertex);
t_vector		vertex_getPos(t_vertex vertex);

t_coord			cinit(float x, float y);
t_coord			csub(t_coord v1, t_coord v2);
t_coord			cadd(t_coord v1, t_coord v2);
t_coord			cmul(t_coord v1, float l);
t_coord			cnorm(t_coord v1);
float			cdot(t_coord v1, t_coord v2);
float			clen(t_coord v1);

float			ft_atof(char *str);
void			quit_scop(t_data *d);
#endif
