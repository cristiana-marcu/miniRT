################################# VARIABLES ###################################

NAME := bin/miniRT
MAKEFLAGS += --no-print-directory
RM = rm -rf
MK_DIR = mkdir -p $(@D)
SHELL := /bin/bash
UNAME := $(shell uname -s)
MLX_LINK	=	-L mlx/ -lmlx -framework OpenGL -framework AppKit

################################# LINUX PROP ##################################

ifeq ($(UNAME), Linux)
	MLX_LINK = -lmlx -lXext -lX11 -lm -lz
endif

################################# FILES VARS ##################################

LIBFT := libft/libft.a
BUILD_DIR := .build/
SRC_DIR := srcs/
SRC := \
parser/parser.c \
parser/init_mlx.c \
parser/utils/check_range.c \
parser/utils/errors.c \
parser/utils/free_objs.c \
parser/utils/utils.c \
parser/load_elements/load_scene.c \
parser/load_elements/load_ambient.c \
parser/load_elements/load_camera.c \
parser/load_elements/load_light.c \
parser/load_elements/load_sp.c \
canvas/canvas.c \
vectors.c \
ray.c \
camera.c \
render.c \
sphere-plane.c \
cylinder.c \
lights.c
#main.c \

SRC := $(SRC:%=$(SRC_DIR)%)
INC := \
includes/ \
libft/inc/ \
srcs/parser/inc/
OBJS := $(SRC:$(SRC_DIR)%.c=$(BUILD_DIR)%.o)
DEPS := $(OBJS:.o=.d)

################################### FLAGS #####################################

CC = gcc
CFLAGS = -Wall -Wextra #-Werror
CPPFLAGS := -MMD -MP
DEBUGFLAGS = -g3 #-fsanitize=address
INCFLAGS = $(addprefix -I, $(INC))
LINK_FLAGS = $(LIBFT) $(MLX_LINK)

################################### COLORS ####################################

RED_COL :=$(shell tput setaf 1)
GREEN_COL :=$(shell tput setaf 2)
RESET_COL :=$(shell tput sgr0)

################################### RULES #####################################

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(MK_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUGFLAGS) $(OBJS) $(LINK_FLAGS) -o $(NAME)
	@echo "$(GREEN_COL)$(@F) CREATED$(RESET_COL)"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	@if [ ! -d "$@" ]; then $(MK_DIR); fi
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEBUGFLAGS) $(INCFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(dir $(LIBFT))

-include $(DEPS)

clean:
	make clean -C $(dir $(LIBFT))
	$(RM) $(BUILD_DIR)
	@echo "$(RED_COL)$(BUILD_DIR) DELETED$(RESET_COL)"
	@if [ -d "$(BONUS_DIR)$(BUILD_DIR)" ]; then \
		$(RM) $(BONUS_DIR)$(BUILD_DIR); \
		echo "$(RED_COL)$(BONUS_DIR)$(BUILD_DIR) DELETED$(RESET_COL)"; fi

fclean: clean
	make fclean -C $(dir $(LIBFT))
	$(RM) $(dir $(NAME))
	@echo "$(RED_COL)$(dir $(NAME)) DELETED$(RESET_COL)"

re: fclean all

################################ OPT RULES ####################################

print-%:
	$(info '$*'='$($*)')

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"

.PHONY: all clean fclean re gen_dir

#.SILENT:

