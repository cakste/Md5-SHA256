# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acakste <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/23 19:24:22 by acakste           #+#    #+#              #
#    Updated: 2018/09/26 07:15:23 by acakste          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRCS = srcs/main.c srcs/MD5.c srcs/MD5_preprocessing.c srcs/lib.c
OBJ = main.o MD5.o MD5_preprocessing.o lib.o
INCLUDES = includes/
FLAGS = -Wall -Wextra -Werror
LIB = crypt.a

all: $(NAME)

$(NAME):
	@gcc -c $(FLAGS) -I $(INCLUDES) $(SRCS)
	@ar rcs $(LIB) $(OBJ)
	@gcc $(FLAGS) -o $(NAME) $(LIB) libftprintf.a

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(LIB)
	@/bin/rm -f $(NAME)

re: fclean all
