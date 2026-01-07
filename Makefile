# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/08 19:50:28 by mgarnier          #+#    #+#              #
#    Updated: 2026/01/07 17:18:28 by mgarnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

# COLOR
GREEN		:= \033[32m
RESET		:= \033[0m

# DIR
DIR			= sources/

# MINISHELL
NAME		= minishell
#HEADER		= -I includes

SRC			= $(DIR)main.c

OBJ			= $(SRC:.c=.o)

all :		$(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)
			@echo "${GREEN}====   $(NAME)   ==== : >>>>>SUCCESS<<<<<${RESET}"

%.o: %.c
			@$(CC) -c $(CFLAGS) $< -o $@

clean:
			@if ls $(OBJ) >/dev/null 2>&1; then \
			echo "${GREEN}====   $(NAME)   ==== : >>>OBJ CLEANED<<<${RESET}"; \
			fi
			@rm -f $(OBJ)

fclean:		clean
			@if ls $(NAME) >/dev/null 2>&1; then \
			echo "${GREEN}====   $(NAME)   ==== : >>>ALL CLEANED<<<${RESET}"; \
			fi
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re