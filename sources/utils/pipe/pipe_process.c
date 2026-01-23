/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:41:57 by jodone            #+#    #+#             */
/*   Updated: 2026/01/23 11:38:38 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	child_process(t_pipe *child, t_line *line, t_var *lst_var)
{
	if (child->prev_fd != -1)
		if (dup_and_close(child->prev_fd, STDIN_FILENO) == -1)
		{
			free_all(line, lst_var);
			close_file(child, "dup error\n");
		}
	if (child->index == line->row)
	{
		if (child->fdout != -1)
		{
			if (dup_and_close(child->fdout, STDOUT_FILENO) == -1)
			{
				free_all(line, lst_var);
				close_file(child, "dup error\n");
			}
		}
		if (child->pipefd[1] != -1)
			close(child->pipefd[1]);
	}
	else
	{
		if (dup_and_close(child->pipefd[1], STDOUT_FILENO) == -1)
		{
			free_all(line, lst_var);
			close_file(child, "dup error\n");
		}
	}
	if (child->pipefd[0] != -1)
		close(child->pipefd[0]);
	assignement(line, lst_var, 1);
	free_all(line, lst_var);
	_exit(line->sig);
}

pid_t	pipe_process(t_line *line, t_var *lst_var, t_pipe *child)
{
	pid_t	pid;

	if (child->index != line->row)
	{
		if (pipe(child->pipefd) == -1)
		{
			// écrire message d'erreur
			return (1);
		}
	}
	if (line->row == 1 && !line->red)
	{
		assignement(line, lst_var, 0);
		return (0);
	}
	pid = fork();
	if (pid < 0)
	{
		// écrire message d'erreur
		return (1);
	}
	if (pid == 0)
		child_process(child, line, lst_var);
	else
	{
		if (child->prev_fd != -1)
			close(child->prev_fd);
		if (child->index != line->row)
			child->prev_fd = child->pipefd[0];
		if (child->pipefd[1] != -1)
			close(child->pipefd[1]);
	}
	return (pid);
}
