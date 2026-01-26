/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:30:19 by jodone            #+#    #+#             */
/*   Updated: 2026/01/26 15:58:56 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

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

int	dup_and_close(int fd, int redirect)
{
	if (dup2(fd, redirect) == -1)
		return (-1);
	close(fd);
	return (0);
}

void	close_file(t_pipe *child, char *message)
{
	close_fd(child->pipefd[0]);
	close_fd(child->pipefd[1]);
	close_fd(child->fdout);
	if (message)
	{
		ft_putstr_fd(message, 2);
		exit(EXIT_FAILURE);
	}
}
