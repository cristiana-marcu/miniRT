# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cristianamarcu <cristianamarcu@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/22 16:47:15 by cmarcu            #+#    #+#              #
#    Updated: 2023/03/11 16:21:00 by cristianama      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	srcs/canvas/canvas.c srcs/math/vectors.c ./main.c ./srcs/ray.c
OBJS	=	$(SRCS:.c=.o)

NAME	=	miniRT

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror -g3 -fsanitize=address
RM	= rm -f
INCLUDES = -I./includes/
MLX	= -L./mlx libmlx.dylib -framework Metal -framework AppKit

INCLUDE_LIBFT	= ./srcs/libft

 %.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -Imlx -c $< -o $@

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(MLX) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY:	all clean fclean re
