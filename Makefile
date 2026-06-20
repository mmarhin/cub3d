# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mruiz-ur <mruiz-ur@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/26 12:00:00 by mamarin-          #+#    #+#              #
#    Updated: 2026/06/18 15:05:49 by mruiz-ur         ###   ########.fr        #
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
			  src/rendering/xpm_parser.c \
			  src/rendering/xpm_utils.c \
			  src/rendering/xpm_cleanup.c \
			  src/rendering/raycasting.c \
			  src/rendering/draw.c \
			  src/rendering/texture_utils.c

SRC_EVENTS	= src/events/hooks.c \
			  src/events/move.c

SRC_CLEANUP	= src/cleanup/cleanup.c

SRC_UTILS	= src/utils/error.c \
			  src/utils/parsing/parse_map_utils.c \
			  src/utils/parsing/parse_textures_utils.c \
			  src/utils/parsing/parse_color_utils.c \

SRC_UTILS	+= src/utils/parsing/parse_utils.c

SRCS		= $(SRC_MAIN) $(SRC_PARSING) $(SRC_RENDER) $(SRC_EVENTS) \
			  $(SRC_CLEANUP) $(SRC_UTILS)

OBJ_DIR		= obj
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# ---------------------------------------------------------------------------- #
#  Libraries                                                                     #
# ---------------------------------------------------------------------------- #

LIBFT_DIR	= ./libs/Libft
LIBFT		= $(LIBFT_DIR)/libft.a

# MLX42
MLX_DIR		= ./libs/MLX42
MLX         = $(MLX_DIR)/build/libmlx42.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MLX_FLAGS   = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
else
	MLX_FLAGS   = $(MLX_DIR)/build/libmlx42.a $(MLX_DIR)/build/_deps/glfw-build/src/libglfw3.a -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
endif

# ---------------------------------------------------------------------------- #
#  Rules                                                                         #
# ---------------------------------------------------------------------------- #

all: libmlx $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -lm -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
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
	rm -rf $(OBJ_DIR)
	rm -f $(SRCS:.c=.o)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
