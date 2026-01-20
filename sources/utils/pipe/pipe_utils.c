/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:30:19 by jodone            #+#    #+#             */
/*   Updated: 2026/01/20 13:47:19 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	return_value(int status)
{
	int	result;

	result = 0;
	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		result = WTERMSIG(status) + 128;
	else if (WIFSTOPPED(status))
		result = WSTOPSIG(status) + 128;
	return (result);
}

void	dup_and_close(t_pipe *child, int fd, int redirect)
{
	if (dup2(fd, redirect) == -1)
		close_file(child, "dup error\n");
	close(fd);
}

void	close_file(t_pipe *child, char *message)
{
	if (child->fdin != -1)
		close(child->fdin);
	if (child->fdout != -1)
		close(child->fdout);
	if (child->pipefd[0] != -1)
		close(child->pipefd[0]);
	if (child->pipefd[1] != -1)
		close(child->pipefd[1]);
	if (message)
	{
		ft_putstr_fd(message, 2);
		exit(EXIT_FAILURE);
	}
}
