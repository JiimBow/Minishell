/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:50:13 by jodone            #+#    #+#             */
/*   Updated: 2026/01/13 18:10:00 by jodone           ###   ########.fr       */
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

typedef enum e_token
{
	BUILT_IN,
	COMMANDS,
	OPTIONS,
	FILES,
	DIRECTORIES,
	OPERATORS,
	END
}	t_token;

typedef struct s_arg
{
	char	*content;
	t_token	group;
}	t_arg;

typedef struct s_env
{
	char	**env;
}	t_env;

typedef struct s_line
{
	char	*line;
	char	**args;
}	t_line;

// INITIALIZATION
t_env	*ft_get_env(char **envp);

// PARSING
t_arg	*tokenisation(char **args, int i);
char	*find_cmd_path(char *cmd, char **envp, int i, char *full_path);
char	**ft_split_line(char **env, char const *s, char c, unsigned int line, int i);

// EXECUTING
int		ft_pwd(void);
int		ft_cd(char **argv, char **envp);
void	ft_env(char	**envp);
void	ft_echo(char **args);
void	ft_unset(t_env *env, char **args);
void	free_before_exit(t_line *line, t_env *env, t_arg *data, int sig_return);
int		process(char **cmd, t_env *env);
char	*get_env_path(char *str, char **envp, int *i);

// MEMORY MANAGEMENT
void	pointer_free(char **str);
void	free_double_tab(char **tab);
void	free_struct(t_arg *data);

#endif