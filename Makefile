# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 23:57:50 by jyriarte          #+#    #+#              #
#    Updated: 2025/01/29 17:32:52 by jyriarte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

LIBFT_PATH=libft
LIBFT=$(LIBFT_PATH)/libft.a
LIBFT_FLAG= -L$(LIBFT_PATH) -lft

MLX_PATH=mlx
MLX=$(MLX_PATH)/libmlx_Linux.a
MLX_FLAG= -L${MLX_PATH} -lm -lmlx_Linux -lXext -lX11

CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -I. -I$(LIBFT_PATH) -I$(MLX_PATH) -O3

SOURCES = src/so_long.c src/init_data.c src/error_handler.c src/init_map.c \
		  src/map_checks.c src/map_checks_utils.c src/init_imgs.c \
		  src/render.c src/free_data.c src/render_map.c src/render_utils.c \
		  src/hooks.c src/player.c src/display_moves.c src/black_hole.c

OBJECTS = $(SOURCES:.c=.o)

$(NAME): $(LIBFT) $(MLX) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAG) $(MLX_FLAG)
	@echo "$(NAME) OK!"

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_PATH)

$(MLX):
	@$(MAKE) --no-print-directory -C $(MLX_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@  

bonus: all

all: $(NAME)

clean:
	@$(RM) $(OBJECTS) 
	@$(MAKE) --no-print-directory -C $(LIBFT_PATH) clean
	@$(MAKE) --no-print-directory -C $(MLX_PATH) clean

fclean: clean
	@$(RM) $(NAME) 
	@$(RM) $(LIBFT)

re: fclean all

.PHONY: all re clean fclean bonus
