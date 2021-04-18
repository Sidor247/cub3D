# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwhis <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/01 19:18:04 by cwhis             #+#    #+#              #
#    Updated: 2021/04/18 17:13:54 by cwhis            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -O3
NAME=libft.a
SOURCES		=	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c\
			ft_isprint.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
			ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c\
			ft_strlen.c ft_strncmp.c ft_strrchr.c ft_tolower.c ft_strnstr.c\
			ft_toupper.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c\
			ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c\
			ft_putendl_fd.c ft_putnbr_fd.c
BSOURCES	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJECTS=$(SOURCES:.c=.o)
BOBJECTS=$(BSOURCES:.c=.o)
.PHONY: all clean fclean re bonus bclean

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	@echo "\n\033[0;32mCompiling libft files complited!\033[0m\n"

%.o: %.c
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJECTS) $(BOBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(BOBJECTS)
	ar rc $(NAME) $(BOBJECTS)
	@echo "\n\033[0;32mCompiling libft bonus files completed!\033[0m"