# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwhis <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/26 19:57:38 by igorlebedev       #+#    #+#              #
#    Updated: 2021/10/31 00:19:29 by cwhis            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -O3
NAME=cub3D
MLX=libmlx.dylib
MLXFLAGS=-framework AppKit -framework OpenGL
LIBFT=srcs/libft/libft.a
SRCS		=	$(addprefix srcs/,\
				game_objects/item.c\
				game_objects/weapons.c\
				game_objects/rocket_launcher\
				game_objects/chaingun.c\
				gnl/get_next_line.c\
				gnl/get_next_line_utils.c\
				graphics/draw.c\
				graphics/effects.c\
				graphics/raycasting.c\
				graphics/draw_sprites.c\
				graphics/draw_hud.c\
				graphics/draw_weapon.c\
				graphics/sprites.c\
				graphics/stencil_buf.c\
				input/keys.c\
				input/mouse.c\
				parser/parser.c\
				parser/parse_map.c\
				parser/check.c\
				parser/check_map.c\
				parser/atlas_utils.c\
				parser/parser_utils.c\
				parser/parse_hud.c\
				parser/parse_weapons.c\
				physics/collision.c\
				physics/moves.c\
				physics/vector.c\
				utils/sort_sprites.c\
				utils/free.c\
				utils/create_bmp.c\
				utils/utils.c\
				utils/structs.c\
				cub3d.c\
				mlx_start.c\
				mlx_error.c)
OBJS=$(SRCS:.c=.o)
HEADER=cub3d.h settings.h

all: $(NAME)	

$(NAME): $(OBJS) $(LIBFT) $(MLX) $(HEADER)
	@echo "\n\033[0;33mCompiling cub3D...\033[0m\n"
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "\n\033[0;32mcub3D is ready to start\033[0m\n"

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(LIBFT):
	@echo "\n\033[0;33mCompiling libft...\033[0m\n"
	@cd srcs/libft && $(MAKE) && $(MAKE) bonus
	@cd ../..

$(MLX):
	@echo "\n\033[0;33mCompiling MinilibX...\033[0m\n"
	@cd mlx && $(MAKE) && mv $(MLX) ../ && cd ..

clean:
	@echo "\n\033[0;33mcub3D cleaning...\033[0m\n"
	rm -rf $(OBJS)
	@echo "\n\033[0;31mobjects was successfully deleted\033[0m"
	@echo "\n\033[0;33mDeleting libft...\033[0m\n"
	@cd srcs/libft && $(MAKE) fclean && cd ../..
	@echo "\n\033[0;31mlibft was successfully deleted\033[0m"
	@echo "\n\033[0;33mDeleting MinilibX...\033[0m\n"
	@cd mlx && $(MAKE) clean && cd ..
	@echo "\n\033[0;31mMinilibX was successfully deleted\033[0m\n"

fclean: clean
	@echo "\033[0;33mDeleting cub3D...\033[0m\n"
	rm -rf $(NAME) $(MLX)
	@echo "\n\033[0;31mcub3D was successfully deleted\033[0m\n"

re: fclean all
	@echo "\033[0;34mRemacking completed\033[0m\n"

norm:
	norminette $(SRCS) $(HEADER)

.PHONY: all clean fclean re norm