# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/08 19:50:28 by mgarnier          #+#    #+#              #
#    Updated: 2026/01/08 12:06:35 by jodone           ###   ########.fr        #
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
HEADER		= -I includes \
			-I Great_Libft/Libft \
			-I Great_Libft/ft_printf \
			-I Great_Libft/GNL

SRC			= $(DIR)main.c \
			$(DIR)find_path.c \
			$(DIR)cmd_process.c

OBJ			= $(SRC:.c=.o)

LIBFT= ./Great_Libft/g_libft.a

all :		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			@$(CC) $(CFLAGS) $(HEADER) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
			@echo "${GREEN}====   $(NAME)   ==== : >>>>>SUCCESS<<<<<${RESET}"

$(LIBFT):
		@$(MAKE) -C Great_Libft --no-print-directory

%.o: %.c
			@$(CC) -c $(CFLAGS) $(HEADER) $< -o $@

clean:
			@if ls $(OBJ) >/dev/null 2>&1; then \
			echo "${GREEN}====   $(NAME)   ==== : >>>OBJ CLEANED<<<${RESET}"; \
			fi
			@rm -f $(OBJ)
			@$(MAKE) -C Great_Libft clean --no-print-directory

fclean:		clean
			@if ls $(NAME) >/dev/null 2>&1; then \
			echo "${GREEN}====   $(NAME)   ==== : >>>ALL CLEANED<<<${RESET}"; \
			fi
			@rm -f $(NAME)
			@$(MAKE) -C Great_Libft fclean --no-print-directory

re:			fclean all

.PHONY:		all clean fclean re