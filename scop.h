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
# define NUM_BUFFERS 1
# define POSITION_VB 0
# define NUM_SHADERS 2
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

typedef	struct	s_vertex
{
	t_vector	pos;
}				t_vertex;


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
}				t_shader;

typedef	struct	s_data
{
	GLenum		status;
	int			run;

}				t_data;

void			shader_init(char *filename, t_shader *shader);
void			shader_del(t_shader *shader);
GLuint			shader_create(char *text, GLenum shaderType);
void			shader_bind(t_shader *shader);
char			*shader_load(const char *filename);

void mesh_init(t_vertex * vertices, unsigned int num, t_mesh * mesh);
void mesh_del(t_mesh *mesh);
void mesh_draw(t_mesh *mesh);

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
t_vertex		vertex_init(t_vector pos);

void	quit_scop(SDL_GLContext glContext, SDL_Window	*window);
#endif
