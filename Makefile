# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frgojard <frgojard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/14 14:20:55 by frgojard          #+#    #+#              #
#    Updated: 2022/11/30 11:11:15 by frgojard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAGS = -Wall -g3 -Wextra -Werror

RM = rm -f

LIBFT = ./libft/libft.a

SRC =	main.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) -L./libft -lft

$(LIBFT) :
	make -C libft
		
.c.o:
	$(CC) $(CFLAGS) -o $@ -c $< -I . -I libft

clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean:	clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
