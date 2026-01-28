/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:41:57 by jodone            #+#    #+#             */
/*   Updated: 2026/01/28 18:03:04 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup_fd_file(t_pipe *child, t_line *line, t_var *lst_var)
{
	if (child->prev_fd != -1)
	{
		if (dup_and_close(child->prev_fd, STDIN_FILENO) == -1)
		{
			free_all(line, lst_var);
			close_file(child, "dup error\n");
		}
	}
	if (child->fdout != -1)
	{
		if (dup_and_close(child->fdout, STDOUT_FILENO) == -1)
		{
			free_all(line, lst_var);
			close_file(child, "dup error\n");
		}
		return (1);
	}
	return (0);
}

void	child_process(t_pipe *child, t_line *line, t_var *lst_var)
{
	int	exit_sig;
	int	fdout_open;

	fdout_open = dup_fd_file(child, line, lst_var);
	if (child->index == line->row)
		close_fd(child->pipefd[1]);
	else
	{
		if (fdout_open == 0)
		{
			if (dup_and_close(child->pipefd[1], STDOUT_FILENO) == -1)
			{
				free_all(line, lst_var);
				close_file(child, "dup error\n");
			}
		}
	}
	close_fd(child->pipefd[0]);
	assignement(line, lst_var, 1);
	exit_sig = line->sig;
	free_all(line, lst_var);
	exit(exit_sig);
}

static void	fork_process(t_line *line, t_var *lst_var, t_pipe *child, int pid)
{
	if (pid == 0)
		child_process(child, line, lst_var);
	else
	{
		close_fd(child->pipefd[1]);
		signal(SIGINT, handle_sig_cmd);
		close_fd(child->prev_fd);
		if (child->index != line->row)
			child->prev_fd = child->pipefd[0];
		if (child->fdout != -1)
		{
			close(child->fdout);
			child->fdout = -1;
		}
		if (child->index == line->row)
			close_fd(child->pipefd[0]);
	}
}

pid_t	pipe_process(t_line *line, t_var *lst_var, t_pipe *child)
{
	pid_t	pid;

	if (child->index != line->row)
	{
		if (pipe(child->pipefd) == -1)
		{
			perror("pipe");
			line->sig = 1;
			return (1);
		}
	}
	if (line->row == 1 && !line->redirec)
	{
		assignement(line, lst_var, 0);
		return (0);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		line->sig = 1;
		return (1);
	}
	fork_process(line, lst_var, child, pid);
	return (pid);
}
