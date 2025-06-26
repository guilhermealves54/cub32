# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 18:20:53 by gribeiro          #+#    #+#              #
#    Updated: 2025/04/04 18:20:53 by gribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

# Srcs
SRCS = src/main.c src/parse.c src/parse_map.c src/fill_map.c \
	src/parse_utils.c src/parse_utils2.c src/memclean.c \
	src/init.c src/raycast.c src/draw_image.c src/game_loop.c
OBJS = $(SRCS:.c=.o)

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Libs
MLX = minilibx-linux/
LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a
INCLUDES = -I./libft

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C ./libft
	@make -s -C $(MLX)
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a $(MLX)libmlx.a -lXext -lX11 -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: all
	./$(NAME) maps/map01.cub

clean:
	@make clean -C ./libft
	@make clean -s -C $(MLX)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

valgrind: all
	@valgrind --show-below-main=no --leak-check=full --show-leak-kinds=all \
	--track-origins=yes -s -q ./cub3D maps/map01.cub

.PHONY: all clean fclean re
