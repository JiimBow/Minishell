/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:13:04 by jodone            #+#    #+#             */
/*   Updated: 2026/01/28 11:17:27 by mgarnier         ###   ########.fr       */
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

int	r_here_doc(t_pipe *child, t_line *line, t_var *lst_var, t_var *redirec)
{
	int		pipe_doc[2];
	int		status;
	pid_t	pid;
	char	*tmp;

	(void)child;
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
		close(pipe_doc[0]);
		while (1)
		{
			if (hd_proc(line, lst_var, redirec->content, pipe_doc[1]) == 1)
				break ;
		}
		close(pipe_doc[1]);
		free_all(line, lst_var);
		if (g_sig == SIGINT)
			exit(130);
		exit(EXIT_SUCCESS);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close(pipe_doc[1]);
		// child->prev_fd = pipe_doc[0];
		free(redirec->content);
		redirec->content = NULL;
		waitpid(pid, &status, 0);
		while (1)
		{
			tmp = get_next_line(pipe_doc[0]);
			if (!tmp)
				break ;
			redirec->content = gnl_strjoin(redirec->content, tmp);
			free(tmp);
		}
		// read(pipe_doc[0], redirec->content, )
		close(pipe_doc[0]);
	}
	return (return_value(status));
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

int	open_file(t_line *line, t_pipe *child, t_var *lst_var, int index)
{
	t_var	*tmp;
	int		file_sig;

	(void)lst_var;
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
				child->prev_fd = dup(STDIN_FILENO);
				write(child->prev_fd, tmp->content, ft_strlen(tmp->content));
			}
			else if (tmp->rank == REDIR_OUT)
				file_sig = r_out(child, tmp->content);
			else if (tmp->rank == REDIR_APPEND)
				file_sig = r_append(child, tmp->content);
			if (file_sig == 1 || file_sig == 130)
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
