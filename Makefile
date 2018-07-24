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
SRCS = main.c get_next_line.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror
FFLAGS = -F ~/Library/Frameworks -framework SDL2 -framework SDL2_ttf
CGFLAGS = -framework OpenGL -framework AppKit
INCS = scop.h
JUNK = $(wildcard .DS_Store */.DS_Store */*/.DS_Store *.gch \
		  get_next_line/*.gch)

all:$(NAME)

$(NAME): 
	make -C libft/
	gcc -o $(NAME) $(SRCS) -F ~/Library/Frameworks -framework SDL2 -framework SDL2_ttf libft/libft.a
	rm -rf $(JUNK)
	echo "compiled"

clean:
	@rm -rf $(OBJS)
	@rm -f  get_next_line.h.gch
	@echo "cleaned"

fclean: clean
	@rm -rf $(NAME)
	@echo "fcleaned"

libclean: fclean
	@make fclean -C libft/
	@echo "libcleaned"

re: fclean all
