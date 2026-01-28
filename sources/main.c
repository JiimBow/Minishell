/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:52:55 by jodone            #+#    #+#             */
/*   Updated: 2026/01/28 15:07:41 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <time.h>

long	g_sig = 0;

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

static void	minishell(t_line *line, t_var *lst_var, t_pipe *child)
{
	__pid_t	pid;
	__pid_t	last_pid;
	int		i;

	parse_quote_and_operators(line, lst_var);
	split_pipe(line, lst_var);
	parse_redirection(line, lst_var);
	i = 0;
	if (line->sig == 130)
		return ;
	while (line->block && line->block[i])
	{
		pid = 1;
		child->index = i + 1;
		line->args = split_spaces(line, lst_var, line->block[i]);
		replace_args_without_redirection(line, lst_var);
		if (line->redirec)
			line->sig = open_file(line, child, i);
		if (line->sig != 1)
			last_pid = pipe_process(line, lst_var, child);
		free_double_tab(line->args);
		line->args = NULL;
		i++;
	}
	if (line->sig != 1 && (line->row > 1 || line->redirec))
		get_last_status(pid, last_pid, line);
}

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	t_var	*lst_var;
	t_pipe	child;

	(void)argc;
	(void)argv;
	lst_var = get_var(envp);
	line = creation_line(lst_var);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		reinitialization(line, lst_var, &child);
		if (g_sig == SIGINT)
			global_handle(line, g_sig);
		if (!line->line)
			free_before_exit(line, lst_var);
		minishell(line, lst_var, &child);
		add_history(line->line);
		free_line_struct(line, 0);
		line->prev_sig = line->sig;
	}
	return (0);
}
