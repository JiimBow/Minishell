/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:13:04 by jodone            #+#    #+#             */
/*   Updated: 2026/02/11 17:11:12 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	r_in(t_line *line, t_var *lst_var, t_pipe *child, t_var *tmp)
{
	char	*content_unquote;

	if (tmp->content && tmp->content[0] == '\0')
	{
		write_error(tmp->name, 4);
		return (1);
	}
	content_unquote = strdup_unquote(line, lst_var, tmp->content, 0);
	if (child->prev_fd != -1)
		close_fd(child->prev_fd);
	child->prev_fd = open(content_unquote, O_RDONLY);
	if (child->prev_fd < 0)
	{
		write(2, "minishell: ", 11);
		perror(tmp->content);
		free(content_unquote);
		return (1);
	}
	free(content_unquote);
	return (0);
}

static int	r_out(t_pipe *child, char *content)
{
	if (child->fdout != -1)
		close(child->fdout);
	child->fdout = open(content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
	if (child->fdout != -1)
		close(child->fdout);
	child->fdout = open(content, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (child->fdout < 0)
	{
		write(2, "minishell: ", 11);
		perror(content);
		return (1);
	}
	return (0);
}

static int	write_in_prev_fd(t_var *tmp, t_pipe *child)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		write(2, "minishell: ", 11);
		perror("pipe");
		return (1);
	}
	else
	{
		write(fd[1], tmp->content, ft_strlen(tmp->content));
		close(fd[1]);
		if (child->prev_fd != -1)
			close(child->prev_fd);
		child->prev_fd = fd[0];
	}
	return (0);
}

int	open_file(t_line *line, t_var *lst_var, t_pipe *child, int index)
{
	t_var	*tmp;
	int		file_sig;

	tmp = line->redirec;
	file_sig = 0;
	while (tmp)
	{
		if (tmp->index == index)
		{
			if (tmp->rank == REDIR_IN)
				file_sig = r_in(line, lst_var, child, tmp);
			else if (tmp->rank == REDIR_HEREDOC)
				file_sig = write_in_prev_fd(tmp, child);
			else if (tmp->rank == REDIR_OUT)
				file_sig = r_out(child, tmp->content);
			else if (tmp->rank == REDIR_APPEND)
				file_sig = r_append(child, tmp->content);
			if (file_sig == 1)
				break ;
		}
		tmp = tmp->next;
	}
	if (file_sig == 1)
		child->prev_fd = close_fd(child->prev_fd);
	return (file_sig);
}
