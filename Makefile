CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lX11 -lXext -lm
NAME = test
MLX_DIR = minilibx-linux
MLX_LIB = minilibx-linux/libmlx.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MAP ?= map.ber

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) main.c get_next_line/*.c $(MLX_LIB) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(LIBFT):
	@make bonus -C $(LIBFT_DIR)

clean:
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)

fclean:
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

play: re
	./$(NAME) $(MAP)

val: re
	valgrind --leak-check=full --track-origins=yes ./$(NAME) $(MAP)

fun: re
	funcheck -ac ./$(NAME) $(MAP)
