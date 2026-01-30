# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/08 19:50:28 by mgarnier          #+#    #+#              #
#    Updated: 2026/01/30 16:46:16 by mgarnier         ###   ########.fr        #
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
PIPE		= $(UTILS)pipe/
REDIR		= $(UTILS)redir/

# MINISHELL
NAME		= minishell
HEADER		= -Iincludes \
			-IGreat_Libft/Libft \
			-IGreat_Libft/ft_printf \
			-IGreat_Libft/GNL

SRC			= $(DIR)main.c \
			$(PARSING)parse_line.c \
			$(PARSING)split_spaces.c \
			$(PARSING)parsing_utils.c \
			$(PARSING)split_pipe.c \
			$(PARSING)substr_var.c \
			$(PARSING)substr_var_utils.c \
			$(PARSING)parse_redirection.c \
			$(PARSING)parse_redirection_utils.c \
			$(PARSING)conca_split.c \
			$(PARSING)replace_args.c \
			$(PARSING)split_newline.c \
			$(CMD)find_path.c \
			$(CMD)cmd_process.c \
			$(ENV)get_env.c \
			$(ENV)get_var.c \
			$(ENV)lst_utils.c \
			$(EXPORT)ranking_var.c \
			$(EXPORT)display.c \
			$(EXPORT)parsing_export.c \
			$(PIPE)pipe_utils.c \
			$(PIPE)pipe_process.c \
			$(REDIR)open_file.c \
			$(REDIR)here_doc.c \
			$(REDIR)parse_here_doc.c \
			$(BUILT-IN)ft_pwd.c \
			$(BUILT-IN)ft_cd.c \
			$(BUILT-IN)ft_env.c \
			$(BUILT-IN)ft_echo.c \
			$(BUILT-IN)ft_unset.c \
			$(BUILT-IN)ft_exit.c \
			$(BUILT-IN)ft_export.c \
			$(UTILS)free_functions.c \
			$(UTILS)struct_init.c \
			$(UTILS)ft_atoll.c \
			$(UTILS)signal_management.c \
			$(UTILS)error_management.c

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