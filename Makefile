# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/13 01:33:55 by mschmidt          #+#    #+#              #
#    Updated: 2020/08/22 15:26:52 by mschmidt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = ft_printf.c ft_btoxstr.c ft_itoxstr.c ft_ltostr.c ft_putlong_fd.c \
      ft_tohex.c precision_adjust.c ft_strappd.c \
      parse_spec.c replace_convchar.c  flag_adjust.c 
HEADER = libftprintf.h
OBJ = $(SRC:.c=.o)
CFLAGS = -c -Wall -Wextra -Werror 
INCLUDES = -I $(LIBFT_DIR)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(SRC)
	make -C $(LIBFT_DIR)
	gcc $(CFLAGS) $(INCLUDES) $(SRC)
	cp $(LIBFT) $(NAME)
	ar rc $(NAME) $(OBJ) 
	ranlib $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	/bin/rm -f $(OBJ)

fclean: clean 
	make -C $(LIBFT_DIR) fclean
	/bin/rm -f $(NAME)

re: fclean all

bonus: re

test: $(NAME)
	gcc main.c $(INCLUDES) -L. -lftprintf

debug: $(NAME)
	gcc main.c $(INCLUDES) -L. -lftprintf -g -fsanitize=address 
