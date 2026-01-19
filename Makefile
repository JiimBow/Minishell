# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/08 19:50:28 by mgarnier          #+#    #+#              #
#    Updated: 2026/01/19 15:30:19 by jodone           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

# COLOR
GREEN		:= \033[32m
RESET		:= \033[0m

# DIR
DIR			= sources/
OBJ_DIR		= objects
BUILT-IN	= $(DIR)built-in/
PARSING		= $(DIR)parsing/
UTILS		= $(DIR)utils/
CMD			= $(UTILS)cmd/
ENV			= $(UTILS)env/
EXPORT		= $(UTILS)export/

# MINISHELL
NAME		= minishell
HEADER		= -Iincludes \
			-IGreat_Libft/Libft \
			-IGreat_Libft/ft_printf \
			-IGreat_Libft/GNL

SRC			= $(DIR)main.c \
			$(PARSING)parse_line.c \
			$(PARSING)split_line.c \
			$(PARSING)split_utils.c \
			$(PARSING)swap_variable.c \
			$(PARSING)tokenisation.c \
			$(CMD)find_path.c \
			$(CMD)cmd_process.c \
			$(ENV)get_env.c \
			$(ENV)get_var.c \
			$(ENV)lst_utils.c \
			$(EXPORT)ranking_var.c \
			$(EXPORT)display.c \
			$(EXPORT)parsing_export.c \
			$(BUILT-IN)ft_pwd.c \
			$(BUILT-IN)ft_cd.c \
			$(BUILT-IN)ft_env.c \
			$(BUILT-IN)ft_echo.c \
			$(BUILT-IN)ft_unset.c \
			$(BUILT-IN)ft_exit.c \
			$(BUILT-IN)ft_export.c \
			$(UTILS)free_line_struct.c 

OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT= ./Great_Libft/g_libft.a

all :		$(NAME)

$(NAME):	$(OBJ) $(LIBFT)
			@$(CC) $(CFLAGS) $(HEADER) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
			@echo "${GREEN}====   $(NAME)   ==== : >>>>>SUCCESS<<<<<${RESET}"

$(LIBFT):
		@$(MAKE) -C Great_Libft --no-print-directory

$(OBJ_DIR)/%.o: %.c
			@mkdir -p $(dir $@)
			@$(CC) -c $(CFLAGS) $(HEADER) $< -o $@

clean:
			@if ls $(OBJ) >/dev/null 2>&1; then \
			echo "${GREEN}====   $(NAME)   ==== : >>>OBJ CLEANED<<<${RESET}"; \
			fi
			@rm -f $(OBJ)
			@rm -rf $(OBJ_DIR)
			@$(MAKE) -C Great_Libft clean --no-print-directory

fclean:		clean
			@if ls $(NAME) >/dev/null 2>&1; then \
			echo "${GREEN}====   $(NAME)   ==== : >>>ALL CLEANED<<<${RESET}"; \
			fi
			@rm -f $(NAME)
			@$(MAKE) -C Great_Libft fclean --no-print-directory

re:			fclean all

.PHONY:		all clean fclean re