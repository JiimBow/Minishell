# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 14:03:28 by jodone            #+#    #+#              #
#    Updated: 2026/01/08 22:31:38 by mgarnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libftprintf.a
INCLUDES=-I .
CC=cc
FILES= 	ft_bzero.c \
		ft_strlen.c \
		ft_putnbr_base.c \
		ft_uputnbr_base.c \
		ft_itoax.c \
		ft_putstr_print.c \
		ft_putchar_print.c \
		ft_ulputnbr_ptr.c \
		ft_printf.c 
CFLAGS=-Wall -Wextra -Werror
OBJECT=$(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
		@ar rcs $(NAME) $(OBJECT)

%.o: %.c
		@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
		@rm -f $(OBJECT)

fclean: clean
		@rm -f $(NAME)
		
re: fclean all
