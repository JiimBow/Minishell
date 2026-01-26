/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:13:04 by jodone            #+#    #+#             */
/*   Updated: 2026/01/26 16:41:19 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <minishell.h>
#include <unistd.h>

int	r_in(t_pipe *child, char *content)
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

int	r_here_doc(t_pipe *child, t_line *line, char *content)
{
	char	*until_lim;
	int		pipe_doc[2];

	// struct termios t;
	// tcgetattr(STDIN_FILENO, &t);
	if (pipe(pipe_doc) == -1)
	{
		perror("pipe");
		return (1);
	}
	until_lim = NULL;
	while (1)
	{
		if (here_doc_proc(line, until_lim, content, pipe_doc[1]) == 1)
			break ;
	}
	close(pipe_doc[1]);
	child->prev_fd = pipe_doc[0];
	return (0);
}

int	r_out(t_pipe *child, char *content)
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

int	r_append(t_pipe *child, char *content)
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

int	open_file(t_line *line, t_pipe *child)
{
	t_var	*tmp;
	int		file_sig;

	tmp = line->red;
	file_sig = 0;
	while (tmp)
	{
		if (tmp->rank == REDIR_IN)
			file_sig = r_in(child, tmp->content);
		else if (tmp->rank == REDIR_HEREDOC)
			file_sig = r_here_doc(child, line, tmp->content);
		else if (tmp->rank == REDIR_OUT)
			file_sig = r_out(child, tmp->content);
		else if (tmp->rank == REDIR_APPEND)
			file_sig = r_append(child, tmp->content);
		if (file_sig == 1)
			break ;
		tmp = tmp->next;
	}
	return (file_sig);
}
