# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: izelensk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/07 12:17:24 by izelensk          #+#    #+#              #
#    Updated: 2017/08/07 16:21:45 by izelensk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = scop
SRCS = main.c get_next_line.c vector.c colors.c mesh.c shader.c textures.c stb_image.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
FFLAGS = -framework OpenGL -framework AppKit -F ~/Library/Frameworks \
 -framework SDL2 -framework SDL2_ttf 
INCS = scop.h stb_image.h
JUNK = $(wildcard .DS_Store */.DS_Store */*/.DS_Store *.gch \
		  get_next_line/*.gch)

all:$(NAME)

$(NAME): 
	@make -C libft/
	@make -C libglew/
	@gcc -o $(NAME) $(SRCS) $(FFLAGS) libft/libft.a -I libglew/include libglew/lib/libGLEW.a 
	@rm -rf $(JUNK)
	@echo "compiled"

clean:
	@rm -rf $(OBJS)
	@rm -f  get_next_line.h.gch
	@echo "cleaned"

fclean: clean
	@rm -rf $(NAME)
	@echo "fcleaned"

libclean: fclean
	@make fclean -C libft/
	@make clean -C libglew/
	@echo "libcleaned"

re: fclean all
