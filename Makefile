CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lX11 -lXext -lm
NAME = test
MLX_DIR = minilibx-linux
MLX_LIB = minilibx-linux/libmlx.a

all: $(NAME)

$(NAME): $(MLX_LIB)
	$(CC) $(CFLAGS) main.c $(MLX_LIB) -o $(NAME) $(LDFLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@make clean -C $(MLX_DIR)

fclean:
	rm -f $(NAME)

re: fclean all

t: re
	./$(NAME)
