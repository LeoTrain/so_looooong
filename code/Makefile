MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
MLX_FLAGS = -lX11 -lXext -lm

FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

CC = cc -std=gnu11
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address $(MLX_INC)
LDFLAGS = $(MLX_FLAGS)
LDFLAGS += -g -fsanitize=address
SRCS = get_next_*.c utils_*.c init_game.c event_loops.c main.c
OBJS = $(SRCS:.c=.o)

NAME = so_long
MAP_DIR = maps
MAP ?= map.ber

all: $(NAME)

$(NAME): $(FT_PRINTF) $(MLX_LIB) $(OBJS)
	$(CC) $(OBJS) $(MLX_LIB) $(FT_PRINTF) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(FT_PRINTF):
	@make -C $(FT_PRINTF_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@make clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bear: all
	bear -- make
