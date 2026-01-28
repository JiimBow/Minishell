/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:04:05 by jodone            #+#    #+#             */
/*   Updated: 2026/01/28 15:13:54 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	r_here_doc(t_line *line, t_var *lst_var, t_var *redirec)
{
	int		pipe_doc[2];
	int		status;
	pid_t	pid;
	char	*tmp;

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
		close(pipe_doc[0]);
		signal(SIGINT, handle_sign_here_d);
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
		close(pipe_doc[1]);
		signal(SIGINT, SIG_IGN);
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
		close(pipe_doc[0]);
	}
	return (return_value(status));
}

char	*loop_readline(char *content)
{
	char	*until_lim;
	int		empty_line;

	empty_line = 0;
	while (1)
	{
		until_lim = readline("> ");
		if (g_sig == SIGINT)
		{
			if (until_lim)
				free(until_lim);
			return (NULL);
		}
		if (until_lim)
			break ;
		if(!until_lim && empty_line == 0)
		{
			ft_putstr_fd("minishell: warning: here-document at line ", 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(content, 2);
			ft_putstr_fd("')\n", 2);
			return (NULL);
		}
		free(until_lim);
		empty_line = 1;
	}
	return (until_lim);
}

int	hd_proc(t_line *line, t_var *lst_var, char *content, int pipe_doc)
{
	char	*until_lim;

	until_lim = loop_readline(content);
	if (!until_lim)
		return (1);
	if (ft_strncmp(until_lim, content, ft_strlen(content)) == 0
		&& (until_lim[ft_strlen(content)] == '\n'
			|| until_lim[ft_strlen(content)] == '\0'))
	{
		free(until_lim);
		return (1);
	}
	if (line->quote == 0)
		until_lim = substr_var(line, lst_var, until_lim);
	write(pipe_doc, until_lim, ft_strlen(until_lim));
	write(pipe_doc, "\n", 1);
	free(until_lim);
	return (0);
}
