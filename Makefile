# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaylor <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/14 20:26:35 by jaylor            #+#    #+#              #
#    Updated: 2016/12/17 16:03:15 by mchen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf
FILESC = ft_printf.c
FILESO = ft_printf.o
HEADERS = includes
LIBFT_DIR = libft
LIBFT_NAME := ft

all: $(NAME)

$(NAME):
	cd $(LIBFT_DIR) && make
	gcc -Wall -Wextra -Werror -I $(HEADERS) -c $(FILESC)
	gcc -o $(NAME) $(FILESO) -L$(LIBFT_DIR) -l$(LIBFT_NAME)

clean: make_libft_clean
	rm -f $(FILESO)

make_libft_clean:
	cd $(LIBFT_DIR) && make fclean

fclean: clean 
	rm -f $(NAME)

re: fclean all
