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

# define WIDTH 800
# define HEIGHT 800

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

typedef	struct	s_data
{
	GLenum		status;
	int			run;

}				t_data;

#endif
