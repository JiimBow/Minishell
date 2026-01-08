# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/06 11:13:17 by jodone            #+#    #+#              #
#    Updated: 2026/01/08 22:31:55 by mgarnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=GNL.a
INCLUDES=-I .
CC=cc
FILES= 	get_next_line.c \
		get_next_line_utils.c
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

.PHONY: all clean fclean re
