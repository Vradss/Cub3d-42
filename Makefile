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
MLX_DIR = mlx


# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

# Source files - All paths now include SRC_DIR
SRCS =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/gnl/get_next_line.c \
		$(SRC_DIR)/gnl/get_next_line_utils.c \
		$(SRC_DIR)/parser.c \
		$(SRC_DIR)/raycasting.c


# Object files 
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Default rule
all: $(NAME)

# MiniLibX compilation
mlx:
	@make -C $(MLX_DIR)

# Linking rule - Takes objects from OBJ_DIR
$(NAME): mlx $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)
	@echo "$(BLUE) $(NAME) --> Created & compiled 👀$(END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	@mkdir -p $(dir $@) 
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean rule - Removes the OBJ_DIR contents and then the directory
clean:
	@echo "$(GREEN) All objects files deleted 💀💀 $(END)"
	@rm -rf $(OBJ_DIR)
	@make -C $(MLX_DIR) clean

# Full clean rule - Calls clean and then removes executable
fclean: clean
	@echo "$(RED) $(NAME) deleted 💀💀 $(END)"
	@rm -f $(NAME)

# Rebuild rule
re: fclean all

# Phony targets
.PHONY: all clean fclean re mlx