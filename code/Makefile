# Détection de l'OS
UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
	MLX_DIR = minilibx-linux
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_INC = -I$(MLX_DIR)
	MLX_FLAGS = -lX11 -lXext -lm
else
	MLX_DIR = minilibx-macos-opengl
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_INC = -I$(MLX_DIR)
	MLX_FLAGS = -framework OpenGL -framework AppKit
endif

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address $(MLX_INC)
LDFLAGS = $(MLX_FLAGS)
LDFLAGS += -fsanitize=address
NAME = test
MAP_DIR = maps
MAP ?= map.ber
SRCS = errors.c ft_strdup.c image_loader.c init_game.c collectible*.c render.c event_loops.c get_next_line/*.c *_utils.c main.c

all: $(NAME)

$(NAME): $(MLX_LIB)
	$(CC) $(CFLAGS) $(SRCS) $(MLX_LIB) -o $(NAME) $(LDFLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

play: re
	./$(NAME) $(MAP_DIR)/$(MAP)

val: re
	valgrind --leak-check=full --track-origins=yes ./$(NAME) $(MAP_DIR)/$(MAP)

fun: re
	funcheck -ac ./$(NAME) $(MAP_DIR)/$(MAP)

