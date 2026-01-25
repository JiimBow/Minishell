/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:52:55 by jodone            #+#    #+#             */
/*   Updated: 2026/01/25 21:09:45 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	g_sig = 0;

static void	global_handle(t_line *line)
{
	if (WIFSIGNALED(g_sig))
		line->sig = WTERMSIG(g_sig) + 128;
	g_sig = 0;
}

static void	handle_sigint(int signal)
{
	g_sig = SIGINT;
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf("\n");
		rl_redisplay();
	}
}

void	assignement(t_line *line, t_var *lst_var, int is_fork)
{
	if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "cd", 3) == 0)
		line->sig = ft_cd(line, lst_var);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "pwd", 4) == 0)
		line->sig = ft_pwd(lst_var);
	else if (line->args && line->args[0] && !line->args[1]
		&& ft_strncmp(line->args[0], "env", 4) == 0)
		line->sig = ft_env(line->env);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "echo", 5) == 0)
		line->sig = ft_echo(line->args);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "unset", 6) == 0)
		line->sig = ft_unset(line, &lst_var);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "exit", 5) == 0)
		line->sig = free_before_exit(line, lst_var);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "export", 7) == 0)
		line->sig = ft_export(line, &lst_var, line->args);
	else if (line->args)
		line->sig = process(line, lst_var, is_fork);
}

static void	get_last_status(__pid_t pid, __pid_t last_pid, t_line *line)
{
	int	last_status;
	int	status;

	while (pid > 0)
	{
		if (pid == last_pid)
			last_status = status;
		pid = wait(&status);
	}
	line->sig = return_value(last_status);
}

static void	minishell(t_line *line, t_var *lst_var, t_pipe *child, int i)
{
	__pid_t	pid;
	__pid_t	last_pid;

	line->new = parse_line(line);
	line->block = split_pipe(line);
	while (line->block && line->block[i])
	{
		if (line->red)
			ft_lstclear_var(&line->red, free);
		pid = 1;
		child->index = i + 1;
		line->block[i] = substr_var(line, line->block[i]);
		line->sig = 0;
		line->args = split_spaces(line->block[i++]);
		separate_redirection(line);
		if (line->red)
			line->sig = open_file(line, child);
		if (line->sig != 1)
			last_pid = pipe_process(line, lst_var, child);
		free_double_tab(line->args);
		line->args = NULL;
	}
	if (line->sig != 1 && (line->row > 1 || line->red))
		get_last_status(pid, last_pid, line);
}

static void	initialization_struct(t_line *line, t_var *lst_var, t_pipe *child)
{
	line->env = ft_copy_env(&lst_var);
	line->args = NULL;
	line->block = NULL;
	line->red = NULL;
	*child = pipe_init();
}

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	t_var	*lst_var;
	t_pipe	child;

	(void)argc;
	(void)argv;
	lst_var = NULL;
	get_var(&lst_var, envp);
	line = creation_line();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		initialization_struct(line, lst_var, &child);
		line->line = readline("minishell> ");
		if (g_sig == SIGINT)
			global_handle(line);
		if (!line->line)
			free_before_exit(line, lst_var);
		else
		{
			minishell(line, lst_var, &child, 0);
			add_history(line->line);
			free_line_struct(line, 0);
		}
	}
	return (0);
}
