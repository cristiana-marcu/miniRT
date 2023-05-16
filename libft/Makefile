NAME := libft.a

MAKEFLAGS += --no-print-directory

MK_DIR = mkdir -p $(@D)

BASIC_SRC := \
ft_isalpha.c 	\
ft_isdigit.c 	\
ft_isalnum.c 	\
ft_isascii.c 	\
ft_isprint.c 	\
ft_strlen.c 	\
ft_memset.c 	\
ft_bzero.c 		\
ft_memcpy.c 	\
ft_memmove.c 	\
ft_strlcpy.c 	\
ft_strlcat.c 	\
ft_toupper.c 	\
ft_tolower.c	\
ft_strchr.c 	\
ft_strrchr.c	\
ft_memchr.c 	\
ft_calloc.c 	\
ft_strncmp.c	\
ft_memcmp.c 	\
ft_atoi.c		\
ft_strdup.c 	\
ft_strnstr.c	\
ft_substr.c 	\
ft_strjoin.c	\
ft_strtrim.c	\
ft_split.c		\
ft_itoa.c		\
ft_strmapi.c	\
ft_striteri.c	\
ft_putchar_fd.c	\
ft_putstr_fd.c	\
ft_putendl_fd.c	\
ft_putnbr_fd.c	\
ft_lstnew_bonus.c		\
ft_lstadd_front_bonus.c	\
ft_lstsize_bonus.c		\
ft_lstlast_bonus.c		\
ft_lstadd_back_bonus.c	\
ft_lstdelone_bonus.c	\
ft_lstclear_bonus.c		\
ft_lstiter_bonus.c		\
ft_lstmap_bonus.c

EXTRA_SRC := \
ft_str_ends_with.c		\
ft_strjoin_free.c		\
ft_just_strchr.c		\
ft_free_matrix.c		\
ft_dup_matrix.c			\
ft_len_matrix.c			\
ft_isspace.c			\
ft_lstswap.c			\
ft_lstpenult.c			\
ft_atof.c				\
ft_strtod.c				

GNL_SRC := \
get_next_line.c \
get_next_line_utils.c

PRINTF_SRC := \
ft_printf.c 		\
ft_printf_utils.c 	\
ft_put_ptr.c 		\
ft_putnbr_hex.c 	\
ft_putnbr_int.c 	\
ft_putnbr_uns.c

SRC_DIR := src/

BUILD_DIR := .build/

SRC := $(addprefix $(SRC_DIR),		\
$(addprefix basic/, $(BASIC_SRC)) 	\
$(addprefix extra/, $(EXTRA_SRC)) 	\
$(addprefix gnl/, $(GNL_SRC)) 		\
$(addprefix printf/, $(PRINTF_SRC)))


OBJS := $(SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)

DEPS := $(OBJS:.o=.d)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

CPPFLAGS := -MMD -MP -I inc

AR := ar -rcs

RM = rm -rf

RED_COL :=$(shell tput setaf 1)
GREEN_COL :=$(shell tput setaf 2)
RESET_COL :=$(shell tput sgr0)


all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
#	$(info $(GREEN_COL)CREATED $(NAME)$(RESET_COL))

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(MK_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	$(RM) $(BUILD_DIR)

fclean:	clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

print-%:
	$(info '$*'='$($*)')

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"

.PHONY: all clean fclean re

.SILENT:
