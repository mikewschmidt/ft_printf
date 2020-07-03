# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mschmidt <mschmidt@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/13 01:33:55 by mschmidt          #+#    #+#              #
#    Updated: 2020/05/25 18:11:30 by mschmidt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = ft_printf.c ft_btoxstr.c ft_itoxstr.c ft_ltostr.c ft_putlong_ft.c \
      ft_tohex.c left_adjust precision_adjust.c replace_spec.c replace_stars.c \
      width_adjust.c zeropad_adjust.c
#OBJ = ft_printf.o
OBJ = $(SRC:.c:.o)
CFLAGS =# -Wall -Wextra -Werror //REACTIVATE WHEN DONE!!!!!
LIBFT_DIR = ./libft
INCLUDES = -I $(LIBFT_DIR)
LIBS = $(LIBFT_DIR)/*.o  # <-- Relook at this line again

all: $(NAME)

libft:
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): 
	gcc -c $(CFLAGS) $(INCLUDES) $(SRC)
	ar rc $(NAME) $(OBJ) $(LIBS)
	@### REMOVE LINE BELOW!!!
	gcc main.c $(NAME) 

clean:
	/bin/rm -f $(OBJ)
	@#cd libft && rm -f *.o 

fclean: clean 
	/bin/rm -f $(NAME)
	@#cd libft && rm -f libft.a

re: fclean all

debug:
	gcc -c $(CFLAGS)  $(INCLUDES) $(SRC)
	ar rc $(NAME) $(OBJ) $(LIBS)
	@### REMOVE LINE BELOW!!!
	gcc main.c $(NAME) -g -fsanitize=address 
