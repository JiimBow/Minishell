/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:24:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/16 23:28:56 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	return_value(int status)
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

void	pointer_free(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

static void	exec_process(t_line *line, t_var *lst_var)
{
	char	*path_cmd;
	char	*full_path;

	full_path = NULL;
	path_cmd = find_cmd_path(line->args[0], line->env, 0, full_path);
	if (!path_cmd || execve(path_cmd, line->args, line->env) == -1)
	{
		perror(line->args[0]);
		pointer_free(line->args);
		free_double_tab(line->env);
		free(line->line);
		free(line);
		ft_lstclear_var(&lst_var, free);
		free(path_cmd);
		exit(127);
	}
}

int	process(t_line *line, t_var *lst_var)
{
	__pid_t	pid;
	int		status;
	int		sig_return;

	if (!line->args || !*line->args)
		return (127);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		exec_process(line, lst_var);
	waitpid(-1, &status, 0);
	sig_return = return_value(status);
	return (sig_return);
}
