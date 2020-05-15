# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/13 01:33:55 by mschmidt          #+#    #+#              #
#    Updated: 2020/05/13 16:56:01 by mschmidt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = ft_printf.c 
OBJ = ft_printf.o
#OBJ = $(SRC:.c:.o)
FLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft

all: $(NAME)

libft:
	$(MAKE) -C libft

$(NAME): libft
	gcc -c $(FLAGS) $(SRC)
	ar rc $(NAME) $(OBJ)
	### REMOVE LINE BELOW!!!
	gcc -I $(LIBFT_DIR) $(SRC) -L $(LIBFT_DIR) -lft

clean:
	rm -f $(OBJ)
	cd libft && rm -f *.o 

fclean: clean 
	rm $(NAME)
	-cd libft && rm -f libft.a

re: fclean all
