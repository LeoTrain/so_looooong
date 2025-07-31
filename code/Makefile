
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
MLX_FLAGS = -lX11 -lXext -lm

CC = cc -std=gnu11
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address $(MLX_INC)
LDFLAGS = $(MLX_FLAGS)
LDFLAGS += -fsanitize=address
SRCS = init_game.c pathfinding.c collectible*.c event_loops.c get_next_line/*.c utils_*.c main.c

NAME = test
MAP_DIR = maps
MAP ?= map.ber

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

play: all
	./$(NAME) $(MAP_DIR)/$(MAP)

val: re
	valgrind --leak-check=full --track-origins=yes ./$(NAME) $(MAP_DIR)/$(MAP)

fun: re
	funcheck -ac ./$(NAME) $(MAP_DIR)/$(MAP)

