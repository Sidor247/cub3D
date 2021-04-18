# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwhis <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/26 19:57:38 by igorlebedev       #+#    #+#              #
#    Updated: 2021/04/18 17:21:03 by cwhis            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -O3
NAME=cub3D
MLX=libmlx.dylib
MLXFLAGS=-framework OpenGL -framework AppKit
LIBFT=srcs/libft/libft.a
SRCS		=	$(addprefix srcs/,\
				cub3d.c\
				mlx_start.c\
				mlx_error.c\
				draw.c\
				raycasting.c\
				sprites.c\
				sort_sprites.c\
				free.c\
				keys.c\
				moves.c\
				create_bmp.c\
				utils.c\
				parser/parser.c\
				parser/parse_map.c\
				parser/check.c\
				parser/check_map.c\
				parser/parser_utils.c\
				gnl/get_next_line.c\
				gnl/get_next_line_utils.c)
OBJS=$(SRCS:.c=.o)
HEADER=cub3d.h

all: $(NAME)	

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "\n\033[0;33mCompiling cub3D...\033[0m\n"
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "\n\033[0;32mcub3D is ready to start!\033[0m\n"

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
	@echo "\n\033[0;31mobjects was successfully deleted!\033[0m"
	@echo "\n\033[0;33mDeleting libft...\033[0m\n"
	@cd srcs/libft && $(MAKE) fclean && cd ../..
	@echo "\n\033[0;31mlibft was successfully deleted!\033[0m"
	@echo "\n\033[0;33mDeleting MinilibX...\033[0m\n"
	rm -f $(MLX)
	@cd mlx && $(MAKE) clean && cd ..
	@echo "\n\033[0;31mMinilibX was successfully deleted!\033[0m\n"

fclean: clean
	@echo "\033[0;33mDeleting cub3D...\033[0m\n"
	rm -rf $(NAME)
	@echo "\n\033[0;31mcub3D was successfully deleted!\033[0m\n"

re: fclean all
	@echo "\033[0;34mRemacking comleted!\033[0m\n"

norm:
	norminette $(SRCS) $(HEADER)

.PHONY: all clean fclean re norm