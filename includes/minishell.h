/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:50:13 by jodone            #+#    #+#             */
/*   Updated: 2026/01/20 11:04:09 by mgarnier         ###   ########.fr       */
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

typedef struct s_line
{
	char	*line;
	char	*new;
	char	**block;
	int		row;
	char	**args;
	char	**env;
	int		sig;
}	t_line;

typedef struct s_var
{
	char			*name;
	char			*content;
	int				rank;
	struct s_var	*next;
}	t_var;

extern int	g_sig;

// INITIALIZATION
t_line	*creation_line(void);
char	**ft_copy_env(t_var **lst_var);
void	get_var(t_var **lst_var, char **envp);

// PARSING
t_arg	*tokenisation(char **args, int i);
char	*find_cmd_path(char *cmd, char **envp, int i, char *full_path);
char	**split_line(char *line);
char	**split_pipe(t_line *line);
char	**ft_free_tab(char **tab, int line);
int		is_spaces(char c);
int		is_quote(char c);
char	*substr_var(char **env, char const *s);
char	*parse_line(t_line *line);
int		parse_export(char *args);

// UTILITIES
char	*get_env_path(t_var *lst_var, char *str);
char	*get_env_name(char *line);
t_var	*ft_lst_new_var(char *name, char *content);
void	ft_lstadd_back_var(t_var **lst, t_var *new);
void	ft_lstclear_var(t_var **lst, void (*del)(void *));
int		ft_lstsize_var(t_var *lst);

// RANKING
int		already_sorted(t_var **lst_var);
void	rank_var(t_var **lst_var);

// EXECUTING
int		ft_pwd(t_var *lst_var);
int		ft_cd(t_line *line, t_var *lst_var);
int		ft_env(char	**envp);
int		ft_echo(char **args);
int		ft_unset(t_line *line, t_var **lst_var);
int		ft_export(t_var **lst_var, char **args);
void	display_export(t_var **lst_var);
int		process(t_line *line, t_var *lst_var, int dir);

// MEMORY MANAGEMENT
void	pointer_free(char **str);
void	free_double_tab(char **tab);
void	free_struct(t_arg *data);
int		free_before_exit(t_line *line, t_arg *data, t_var *lst_var);
void	free_line_struct(t_line *line, int all);

#endif