# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarcu <cmarcu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/22 16:47:15 by cmarcu            #+#    #+#              #
#    Updated: 2021/04/23 17:05:33 by cmarcu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/canvas/canvas.c srcs/math/tuples.c ./main.c
OBJS	=	$(SRCS:.c=.o)

NAME	=	miniRT

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -f
INCLUDES = -I./includes/
MLX	= -L./minilibx-linux -lmlx -framework OpenGL -framework AppKit

INCLUDE_LIBFT	= ./srcs/libft

 %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(MLX) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY:	all clean fclean re
