/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:52:55 by jodone            #+#    #+#             */
/*   Updated: 2026/02/10 15:12:21 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	g_sig = 0;

static pid_t	line_block_process(t_line *line, t_var *lst_var, t_pipe *child)
{
	pid_t	last_pid;
	int		i;

	last_pid = 0;
	i = 0;
	while (line->block && line->block[i])
	{
		child->index = i + 1;
		line->args = split_spaces(line, lst_var, line->block[i]);
		line->args = reduce_args_without_redirection(line, lst_var);
		replace_variables(line, lst_var);
		if (line->redirec)
			line->sig = open_file(line, lst_var, child, i);
		if (line->sig != 1)
			last_pid = pipe_process(line, lst_var, child);
		line->args = free_double_tab(line->args);
		line->args = NULL;
		i++;
	}
	return (last_pid);
}

static void	minishell(t_line *line, t_var *lst_var, t_pipe *child, int index)
{
	pid_t	last_pid;
	int		pipe_error_block;

	pipe_error_block = 0;
	line->new = ft_calloc(sizeof(char),
			get_parsed_line_lenght(line->ex_block[index]) + 1);
	if (!line->new)
		error_memory_failed(line, lst_var);
	line->new = set_parsed_line(line->ex_block[index], line->new, 0, 0);
	if (parse_pipe(line, 'q', &pipe_error_block) == 1)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		line->sig = 2;
	}
	split_pipe(line, lst_var);
	last_pid = line->sig;
	if (parse_redirection(line, lst_var, pipe_error_block) == 1)
		return ;
	if (last_pid != 0)
		line->sig = last_pid;
	if (line->sig == 130 || line->sig == 2)
		return ;
	last_pid = line_block_process(line, lst_var, child);
	if (line->sig != 1 && (line->row > 1 || line->redirec))
		get_last_status(1, last_pid, line);
}

void	ex_block_process(t_line *line, t_var *lst_var, t_pipe *child)
{
	int	i;

	i = 0;
	line->ex_block = split_newline(line, lst_var, line->line);
	while (line->ex_block && line->ex_block[i])
	{
		if (i > 0)
		{
			line->env = ft_copy_env(&lst_var);
			if (!line->env)
				error_memory_failed(line, lst_var);
			*child = pipe_init();
		}
		if (line->ex_block[i][0] != '\0')
			add_history(line->ex_block[i]);
		minishell(line, lst_var, child, i);
		i++;
		free_line_struct(line, 0);
	}
	free_line_struct(line, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	t_var	*lst_var;
	t_pipe	child;

	(void)argv;
	if (argc != 1)
	{
		write_error(argv[1], 2);
		exit(127);
	}
	lst_var = get_var(envp);
	line = creation_line(lst_var);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		reinitialization(line, lst_var, &child);
		if (!line->line)
			free_before_exit(line, lst_var);
		ex_block_process(line, lst_var, &child);
		line->ex_block = free_double_tab(line->ex_block);
		line->prev_sig = line->sig;
	}
	return (0);
}
