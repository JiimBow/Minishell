/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:50:13 by jodone            #+#    #+#             */
/*   Updated: 2026/01/30 11:07:43 by jodone           ###   ########.fr       */
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
# include <termios.h>
# include <time.h>
# include <dirent.h>

# define REDIR_IN 1
# define REDIR_HEREDOC 2
# define REDIR_APPEND 3
# define REDIR_OUT 4

typedef struct s_var
{
	char			*name;
	char			*content;
	int				rank;
	int				index;
	struct s_var	*next;
}	t_var;

typedef struct s_line
{
	t_var	*redirec;
	char	*line;
	char	*new;
	char	**ex_block;
	char	**block;
	char	**args;
	char	**env;
	long	sig;
	long	prev_sig;
	int		row;
	int		quote;
	int		is_dir;
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

extern long	g_sig;

// INITIALIZATION
t_pipe	pipe_init(void);
t_var	*get_var(char **envp);
t_line	*creation_line(t_var *lst_var);
char	**ft_copy_env(t_var **lst_var);
void	ex_block_process(t_line *line, t_var *lst_var, t_pipe *child);
void	reinitialization(t_line *line, t_var *lst_var, t_pipe *child);

// PARSING
int		is_quote(char c);
int		is_space(char c);
int		is_operator(char c);
int		parse_word(char *line, int i);
char	*get_name(const char *s);
int		is_redirection(char *args);
int		quotes_unclosed(char *line);
int		skip_spaces(char *tab, int i);
int		get_parsed_line_lenght(char *line);
char	**ft_free_tab(char **tab, int line);
char	*get_content(char **env, char *tab);
int		parse_export(char *name, char *args);
int		parse_pipe(t_line *line, char quote, int *pipe_error_block);
void	split_pipe(t_line *line, t_var *lst_var);
int		parse_redirection(t_line *line, t_var *lst_var, int pipe_error_block);
char	*set_parsed_line(char *line, char *new, int i, int j);
char	**split_spaces(t_line *line, t_var *lst_var, char *block);
char	*substr_var(t_line *line, t_var *lst_var, char *s);
int		syntax_error(char *line, char token, char quote, size_t i);
char	*strdup_unquote(t_line *line, t_var *lst_var, char *s, int j);
char	*find_cmd_path(t_line *line, char **paths, int i, char *full_path);
int		get_size_with_variable(t_line *line, const char *s, int count, int i);
char	*substr_var_unquote(t_line *line, t_var *lst_var, char *s, int *expand);

// UTILITIES
char	*get_env_name(char *line);
int		ft_lstsize_var(t_var *lst);
void	write_error(char *cmd_name, int code);
long	ft_atoll(const char *nptr, int *overf);
char	*get_env_path(t_var *lst_var, char *str);
void	ft_lstadd_back_var(t_var **lst, t_var *new);
void	ft_lstclear_var(t_var **lst, void (*del)(void *));
t_var	*ft_lst_new_var(char *name, char *content, int index);

// RANKING
void	rank_var(t_var **lst_var);
int		already_sorted(t_var **lst_var);

// EXECUTING
int		ft_env(char	**envp);
int		ft_echo(char **args);
int		ft_pwd(t_var *lst_var);
void	display_export(t_var **lst_var);
int		ft_cd(t_line *line, t_var *lst_var);
int		ft_unset(t_line *line, t_var **lst_var);
int		ft_export(t_line *line, t_var **lst_var, char **args);
void	assignement(t_line *line, t_var *lst_var, int is_fork);

// MEMORY MANAGEMENT
void	free_double_tab(char **tab);
void	free_all(t_line *line, t_var *lst_var);
void	free_line_struct(t_line *line, int all);
int		free_before_exit(t_line *line, t_var *lst_var);
void	error_memory_failed(t_line *line, t_var *lst_var);

// PIPE
int		close_fd(int fd);
int		return_value(int status);
int		dup_and_close(int fd, int redirect);
void	close_file(t_pipe *child, char *message);
pid_t	pipe_process(t_line *line, t_var *lst_var, t_pipe *child);

// REDIRECTION
int		open_file(t_line *line, t_var *lst_var, t_pipe *child, int index);
int		r_here_doc(t_line *line, t_var *lst_var, t_var *redirec);
void	replace_args_without_redirection(t_line *line, t_var *lst_var);
int		hd_proc(t_line *line, t_var *lst_var, char *content, int pipe_doc);

// SIGNAL
void	handle_sigint(int signal);
void	handle_sig_cmd(int signal);
void	global_handle(t_line *line);
void	handle_sign_here_d(int signal);
void	get_last_status(__pid_t pid, __pid_t last_pid, t_line *line);

// CONCA_SPLIT
int		ft_count_args(char **args);

#endif