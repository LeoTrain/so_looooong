CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lX11 -lXext -lm
NAME = test
MLX_DIR = minilibx-linux
MLX_LIB = minilibx-linux/libmlx.a
MAP_DIR = maps
MAP ?= map.ber

all: $(NAME)

$(NAME): $(MLX_LIB)
	$(CC) $(CFLAGS) main.c ft_*.c get_next_line/*.c *_utils.c $(MLX_LIB) -o $(NAME) $(LDFLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@make clean -C $(MLX_DIR)

fclean:
	rm -f $(NAME)

re: fclean all

play: re
	./$(NAME) $(MAP_DIR)/$(MAP)

val: re
	valgrind --leak-check=full --track-origins=yes ./$(NAME) $(MAP_DIR)/$(MAP)

fun: re
	funcheck -ac ./$(NAME) $(MAP_DIR)/$(MAP)
