/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:41:57 by jodone            #+#    #+#             */
/*   Updated: 2026/01/22 11:33:46 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	redirection(t_line *line, t_pipe *child, t_var *lst_var)
{
	t_var	*tmp = line->red;
	while (tmp)
	{
		if (tmp->rank == REDIR_IN)
		{
			if (child->prev_fd != -1)
				close(child->prev_fd);
			child->prev_fd = open(tmp->content, O_RDONLY);
			if (child->prev_fd < 0)
			{
				child->prev_fd = open("/dev/null", O_RDONLY);
				write(2, "minishell: ", 11);
				perror(tmp->content);
				free_all(line, lst_var);
				g_sig = 1;
				_exit(g_sig);
			}
			else
			{
				dup2(child->prev_fd, STDIN_FILENO);
				close(child->prev_fd);
			}
		}
		else if (tmp->rank == REDIR_HEREDOC)
		{
			
		}
		else if (tmp->rank == REDIR_OUT)
		{
			if (child->pipefd[1] != -1)
				close(child->pipefd[1]);
			child->pipefd[1] = open(tmp->content, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (child->pipefd[1] < 0)
				perror(tmp->content);
			else
			{
			dup2(child->pipefd[1], STDOUT_FILENO);
			close(child->pipefd[1]);
			}
		}
		else if (tmp->rank == REDIR_APPEND)
		{
			if (child->pipefd[1] != -1)
				close(child->pipefd[1]);
			child->pipefd[1] = open(tmp->content, O_CREAT | O_WRONLY | O_APPEND, 0666);
			if (child->pipefd[1] < 0)
				perror(tmp->content);
			else
			{
				dup2(child->pipefd[1], STDOUT_FILENO);
				close(child->pipefd[1]);
			}
		}
		tmp = tmp->next;
	}
}

void	child_process(t_pipe *child, t_line *line, t_var *lst_var)
{
	if (child->prev_fd != -1)
		dup_and_close(child, child->prev_fd, STDIN_FILENO);
	// else
	// 	dup_and_close(child, child->fdout);
	if (child->index == line->row)
	{
		if (child->pipefd[1] != -1)
			close(child->pipefd[1]);
	}
	else
	{
		dup_and_close(child, child->pipefd[1], STDOUT_FILENO);
		if (child->fdout != -1)
			close(child->fdout);
	}
	if (child->pipefd[0] != -1)
		close(child->pipefd[0]);
	if (line->red)
	{
		redirection(line, child, lst_var);
	}
	assignement(line, lst_var, 1);
	free_all(line, lst_var);
	_exit(g_sig);
}

pid_t	pipe_process(t_line *line, t_var *lst_var, t_pipe *child)
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
