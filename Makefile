# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#              #
#    Updated: 2026/06/09 14:49:03 by mruiz-ur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES 	= -I./includes -I./libs/Libft -I./libs/MLX42/include
# ---------------------------------------------------------------------------- #
#  Sources                                                                       #
# ---------------------------------------------------------------------------- #

SRC_MAIN	= src/main.c

SRC_PARSING	= src/parsing/parse_args.c \
			  src/parsing/read_file.c \
			  src/parsing/parse_textures.c \
			  src/parsing/parse_colors.c \
			  src/parsing/parse_map.c \
			  src/parsing/validate_map.c

SRC_RENDER	= src/rendering/init_mlx.c \
			  src/rendering/load_textures.c \
			  src/rendering/raycasting.c \
			  src/rendering/draw.c \
			  src/rendering/texture_utils.c

SRC_EVENTS	= src/events/hooks.c \
			  src/events/move.c

SRC_CLEANUP	= src/cleanup/cleanup.c

SRC_UTILS	= src/utils/error.c

SRCS		= $(SRC_MAIN) $(SRC_PARSING) $(SRC_RENDER) $(SRC_EVENTS) \
			  $(SRC_CLEANUP) $(SRC_UTILS)

OBJS		= $(SRCS:.c=.o)

# ---------------------------------------------------------------------------- #
#  Libraries                                                                     #
# ---------------------------------------------------------------------------- #

LIBFT_DIR	= ./libs/Libft
LIBFT		= $(LIBFT_DIR)/libft.a

# MLX42
MLX_DIR		= ./libs/MLX42
MLX         = $(MLX_DIR)/build/libmlx42.a
MLX_FLAGS   = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

# ---------------------------------------------------------------------------- #
#  Rules                                                                         #
# ---------------------------------------------------------------------------- #

all: libmlx $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -lm -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4


libmlx:
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4
	
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(MLX_DIR)/build
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
