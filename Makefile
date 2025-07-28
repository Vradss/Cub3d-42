# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vflorez <vflorez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/28 18:53:18 by vflorez           #+#    #+#              #
#    Updated: 2025/07/28 18:53:20 by vflorez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Colors
RED 	= \033[0;91m
GREEN	= \033[1;92m
YELLOW	= \033[1;93m
BLUE	= \033[0;96m
ORANGE	= \033[0;33m
GRAY	= \033[0;90m
END		= \033[0m

# Executable name
NAME = cub3D

# Directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
MLX_DIR_MAC = mlx
MLX_DIR_LINUX = mlx_LINUX

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)
LFLAGS      = -L $(LIBFT_DIR) -lft

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	MLX_DIR = $(MLX_DIR_MAC)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	CFLAGS += -I$(MLX_DIR)
else
	MLX_DIR = $(MLX_DIR_LINUX)
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lz
	CFLAGS += -I$(MLX_DIR)/include
endif

#libft
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Source files - All paths now include SRC_DIR
SRCS =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/gnl/get_next_line.c \
		$(SRC_DIR)/gnl/get_next_line_utils.c \
		$(SRC_DIR)/raycasting.c \
		$(SRC_DIR)/raycasting_render.c \
		$(SRC_DIR)/parser_data.c \
		$(SRC_DIR)/exit_n_free.c \
		$(SRC_DIR)/parser_map.c \
		$(SRC_DIR)/parser_textures.c \
		$(SRC_DIR)/parser_utils.c \
		$(SRC_DIR)/parser_colors.c \
		$(SRC_DIR)/parser_map_valid.c \
		$(SRC_DIR)/parser_players.c \
		$(SRC_DIR)/moves.c \
		$(SRC_DIR)/moves_rotate.c \
		$(SRC_DIR)/texture_loading.c

# Object files 
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default rule
all: $(NAME)

# MiniLibX compilation
mlx:
	@make -C $(MLX_DIR) || true 

$(LIBFT):
	@make -C $(LIBFT_DIR)

# Linking rule - Takes objects from OBJ_DIR
$(NAME): mlx $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX_FLAGS)
	@echo "$(BLUE) $(NAME) --> Created & compiled 👀$(END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	@mkdir -p $(dir $@) 
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean rule - Removes the OBJ_DIR contents and then the directory
clean:
	@echo "$(GREEN) All objects files deleted 💀💀 $(END)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean || true
	@make clean -C $(LIBFT_DIR)

# Full clean rule - Calls clean and then removes executable
fclean: clean
	@echo "$(RED) $(NAME) deleted 💀💀 $(END)"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

# Rebuild rule
re: fclean all

# Phony targets
.PHONY: all clean fclean re mlx