/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:50:13 by jodone            #+#    #+#             */
/*   Updated: 2026/01/23 11:57:18 by jodone           ###   ########.fr       */
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

# define REDIR_IN 1
# define REDIR_HEREDOC 2
# define REDIR_APPEND 3
# define REDIR_OUT 4

typedef struct s_var
{
	char			*name;
	char			*content;
	int				rank;
	struct s_var	*next;
}	t_var;

typedef struct s_line
{
	char	*line;
	char	*new;
	char	**block;
	int		row;
	char	**args;
	t_var	*red;
	char	**env;
	int		sig;
	int		quote;
}	t_line;

typedef struct s_pipe
{
	int	fdout;
	int	pipefd[2];
	int	prev_fd;
	int	index;
}	t_pipe;

typedef struct s_atoll
{
	long	result;
	int		sign;
}	t_atoll;

// extern long	g_sig;

// INITIALIZATION
t_line	*creation_line(void);
t_pipe	pipe_init(void);
char	**ft_copy_env(t_var **lst_var);
void	get_var(t_var **lst_var, char **envp);

// PARSING
char	*find_cmd_path(t_line *line, char **paths, int i, char *full_path);
char	**split_line(char *line);
char	**split_pipe(t_line *line);
void	find_redirection(t_line *line);
char	**ft_free_tab(char **tab, int line);
int		is_spaces(char c);
int		skip_spaces(char *tab, int i);
int		is_quote(char c);
int		is_operator(char c);
char	*substr_var(t_line *line, char *s);
char	*parse_line(t_line *line);
int		parse_export(char *name, char *args);
char	*get_name(const char *s);
char	*get_content(char **env, char *tab);
int		get_count(char **env, const char *s, int *i);
int		get_size_with_variable(t_line *line, const char *s, int count, int i);
int		variable_size(t_line *line, const char *s, int *i, int count);
char	*strdup_unquote(t_line *line, char *s, int i, int j);

// UTILITIES
char	*get_env_path(t_var *lst_var, char *str);
char	*get_env_name(char *line);
t_var	*ft_lst_new_var(char *name, char *content);
void	ft_lstadd_back_var(t_var **lst, t_var *new);
void	ft_lstclear_var(t_var **lst, void (*del)(void *));
int		ft_lstsize_var(t_var *lst);
void	write_error(char *cmd_name, int code);
long	ft_atoll(const char *nptr, int *overf);

// RANKING
int		already_sorted(t_var **lst_var);
void	rank_var(t_var **lst_var);

// EXECUTING
int		ft_pwd(t_var *lst_var);
int		ft_cd(t_line *line, t_var *lst_var);
int		ft_env(char	**envp);
int		ft_echo(char **args);
int		ft_unset(t_line *line, t_var **lst_var);
int		ft_export(t_line *line, t_var **lst_var, char **args);
void	display_export(t_var **lst_var);
int		process(t_line *line, t_var *lst_var, int dir, int is_fork);
void	assignement(t_line *line, t_var *lst_var, int is_fork);

// MEMORY MANAGEMENT
void	pointer_free(char **str);
void	free_double_tab(char **tab);
int		free_before_exit(t_line *line, t_var *lst_var);
void	free_line_struct(t_line *line, int all);
void	free_all(t_line *line, t_var *lst_var);

// PIPE
pid_t	pipe_process(t_line *line, t_var *lst_var, t_pipe *child);
void	close_file(t_pipe *child, char *message);
int		return_value(int status);
int		dup_and_close(int fd, int redirect);

// REDIRECTION
int		open_file(t_line *line, t_pipe *child);
char	*add_nl(char *limiter);

#endif