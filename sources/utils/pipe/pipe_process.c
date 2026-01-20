/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:41:57 by jodone            #+#    #+#             */
/*   Updated: 2026/01/20 16:27:39 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_process(t_pipe *child, t_line *line, t_var *lst_var, t_arg *data)
{
	/* if (child->prev_fd == -1)
		close_file(child, "");*/
	if (child->index > 1)
		dup_and_close(child, child->prev_fd, STDIN_FILENO);
	if (child->index == line->row)
	{
		/* if (child->fdout == -1)
			close_file(child, "");
		dup_and_close(child, child->fdout, STDOUT_FILENO);*/
		close(child->pipefd[1]);
	}
	else
	{
		dup_and_close(child, child->pipefd[1], STDOUT_FILENO);
		if (child->fdout != -1)
			close(child->fdout);
	}
	close(child->pipefd[0]);
	assignement(line, lst_var, data);
	free_all(line, lst_var, data);
	_exit(g_sig);
}

pid_t	pipe_process(t_line *line, t_var *lst_var, t_arg *data, t_pipe *child)
{
	pid_t	pid;

	if (child->index != line->row)
	{
		if (pipe(child->pipefd) == -1)
			close_file(child, "pipe error\n");
	}
	pid = fork();
	if (pid < 0)
		close_file(child, "fork error\n");
	if (pid == 0)
		child_process(child, line, lst_var, data);
	else
	{
		/* if (child->prev_fd != -1)
			close(child->prev_fd);*/
		if (child->index != line->row)
			child->prev_fd = child->pipefd[0];
		close(child->pipefd[1]);
	}
	return (pid);
}
