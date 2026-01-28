/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:13:04 by jodone            #+#    #+#             */
/*   Updated: 2026/01/28 14:53:09 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <minishell.h>

static int	r_in(t_pipe *child, char *content)
{
	child->prev_fd = open(content, O_RDONLY);
	if (child->prev_fd < 0)
	{
		write(2, "minishell: ", 11);
		perror(content);
		return (1);
	}
	return (0);
}

static int	r_out(t_pipe *child, char *content)
{
	child->fdout = open(content, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (child->fdout < 0)
	{
		write(2, "minishell: ", 11);
		perror(content);
		return (1);
	}
	return (0);
}

static int	r_append(t_pipe *child, char *content)
{
	child->fdout = open(content, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (child->fdout < 0)
	{
		write(2, "minishell: ", 11);
		perror(content);
		return (1);
	}
	return (0);
}

int	open_file(t_line *line, t_pipe *child, int index)
{
	t_var	*tmp;
	int		file_sig;
	int		fd[2];

	tmp = line->redirec;
	file_sig = 0;
	while (tmp)
	{
		if (tmp->index == index)
		{
			if (tmp->rank == REDIR_IN)
				file_sig = r_in(child, tmp->content);
			else if (tmp->rank == REDIR_HEREDOC)
			{
				pipe(fd);
				write(fd[1], tmp->content, ft_strlen(tmp->content));
				close(fd[1]);
				if (child->prev_fd != -1)
					close(child->prev_fd);
				child->prev_fd = fd[0];
			}
			else if (tmp->rank == REDIR_OUT)
				file_sig = r_out(child, tmp->content);
			else if (tmp->rank == REDIR_APPEND)
				file_sig = r_append(child, tmp->content);
			if (file_sig == 1)
			{
				if (child->prev_fd != -1)
				{
					close (child->prev_fd);
					child->prev_fd = -1;
				}
				break ;
			}
		}
		tmp = tmp->next;
	}
	return (file_sig);
}
