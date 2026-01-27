/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:13:04 by jodone            #+#    #+#             */
/*   Updated: 2026/01/27 15:46:49 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <minishell.h>

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

int	r_here_doc(t_pipe *child, t_line *line, t_var *lst_var, char *content)
{
	int		pipe_doc[2];
	int		status;
	pid_t	pid;

	if (pipe(pipe_doc) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, handle_sign_here_d);
		while (1)
		{
			if (hd_proc(line, lst_var, content, pipe_doc[1]) == 1)
				break ;
		}
		close(pipe_doc[1]);
		close(pipe_doc[0]);
		free_all(line, lst_var);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		child->prev_fd = pipe_doc[0];
		close(pipe_doc[1]);
		waitpid(-1, &status, 0);
	}
	return (return_value(status));
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

int	open_file(t_line *line, t_pipe *child, t_var *lst_var)
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
			file_sig = r_here_doc(child, line, lst_var, tmp->content);
		else if (tmp->rank == REDIR_OUT)
			file_sig = r_out(child, tmp->content);
		else if (tmp->rank == REDIR_APPEND)
			file_sig = r_append(child, tmp->content);
		if (file_sig == 1 || file_sig == 130)
		{
			if (child->prev_fd != -1)
				close (child->prev_fd);
			break ;
		}
		tmp = tmp->next;
	}
	return (file_sig);
}
