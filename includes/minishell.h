/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:50:13 by jodone            #+#    #+#             */
/*   Updated: 2026/01/12 15:57:56 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <linux/limits.h>
# include <sys/stat.h>

enum e_token
{
	BUILT_IN,
	COMMANDS,
	OPTIONS,
	FILES,
	DIRECTORIES,
	OPERATORS
};

typedef struct s_arg
{
	int				index;
	char			*content;
	enum e_token	group;
}	t_arg;

// PARSING
t_arg	*tokenisation(t_arg *data, char **args, int i);
char	*find_path(char *cmd, char **envp, int i, char *full_path);
char	**ft_split_line(char const *s, char c, unsigned int line, int i);

// EXECUTING
int		ft_pwd(void);
int		ft_cd(char **argv, char **envp);
void	process(char **cmd, char **envp);

// MEMORY MANAGEMENT
void	pointer_free(char **str);
void	free_double_tab(char **tab);

#endif