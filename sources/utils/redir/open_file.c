/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 10:13:04 by jodone            #+#    #+#             */
/*   Updated: 2026/01/22 14:41:21 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	r_in(t_line *line, t_pipe *child, t_var *lst_var, char *content)
{
	if (child->prev_fd != -1)
		close(child->prev_fd);
	child->prev_fd = open(content, O_RDONLY);
	if (child->prev_fd < 0)
	{
		child->prev_fd = open("/dev/null", O_RDONLY);
		write(2, "minishell: ", 11);
		perror(                       content);
		free_all(line, lst_var);
		g_sig = 1;
		_exit(g_sig);
	}
	else
	{
		if (dup_and_close(child->prev_fd, STDIN_FILENO) == -1)
		{
			free_all(line, lst_var);
			close_file(child, "dup error\n");
		}
		close(child->prev_fd);
	}
}

void	r_here_doc(t_line *line, t_pipe *child, t_var *lst_var, char *content)
{
	char	*until_lim;
	// int		pipe_doc[2];

	// if (pipe(pipe_doc) == -1)
	// {
	// 	free_all(line, lst_var);
	// 	close_file(child, "pipe error\n");
	// } 
	until_lim = NULL;
	(void)lst_var;
	(void)line;
	while (1)
	{
		until_lim = get_next_line(STDIN_FILENO);
		if (!until_lim)
			break ;
		if (ft_strncmp(until_lim, content, ft_strlen(content)) == 0
			&& until_lim[ft_strlen(content)] == '\n')
		{
			free(until_lim);
			break ;
		}
		write(child->pipefd[1], until_lim, ft_strlen(until_lim));
		free(until_lim);
	}
	close(child->pipefd[1]);
	// child->pipefd[0] = pipe_doc[0];
}

void	r_out(t_line *line, t_pipe *child, t_var *lst_var, char *content)
{
	if (child->pipefd[1] != -1)
		close(child->pipefd[1]);
	child->pipefd[1] = open(content, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (child->pipefd[1] < 0)
		perror(content);
	else
	{
		if (dup_and_close(child->pipefd[1], STDOUT_FILENO) == -1)
		{
			free_all(line, lst_var);
			close_file(child, "dup error\n");
		}
		close(child->pipefd[1]);
	}
}

void	r_append(t_line *line, t_pipe *child, t_var *lst_var, char *content)
{
	if (child->pipefd[1] != -1)
		close(child->pipefd[1]);
	child->pipefd[1] = open(content, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (child->pipefd[1] < 0)
		perror(content);
	else
	{
		if (dup_and_close(child->pipefd[1], STDOUT_FILENO) == -1)
		{
			free_all(line, lst_var);
			close_file(child, "dup error\n");
		}
		close(child->pipefd[1]);
	}
}

void	open_file(t_line *line, t_pipe *child, t_var *lst_var)
{
	t_var	*tmp;

	tmp = line->red;
	while (tmp)
	{
		if (tmp->rank == REDIR_IN)
			r_in(line, child, lst_var, tmp->content);
		else if (tmp->rank == REDIR_HEREDOC)
			r_here_doc(line, child, lst_var, tmp->content);
		else if (tmp->rank == REDIR_OUT)
			r_out(line, child, lst_var, tmp->content);
		else if (tmp->rank == REDIR_APPEND)
			r_append(line, child, lst_var, tmp->content);
		tmp = tmp->next;
	}
}
