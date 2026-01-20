/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:24:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/20 19:03:43 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	exec_process(t_line *line, t_var *lst_var, int is_dir)
{
	char	*path_cmd;
	char	*full_path;

	full_path = NULL;
	path_cmd = find_cmd_path(line->args[0], line->env, 0, full_path);
	if (!path_cmd || execve(path_cmd, line->args, line->env) == -1
		|| is_dir == 1)
	{
		perror(line->args[0]);
		free_line_struct(line, 1);
		ft_lstclear_var(&lst_var, free);
		free(path_cmd);
		if (is_dir == 1)
			exit(126);
		exit(127);
	}
}

int	process(t_line *line, t_var *lst_var, int dir, int is_fork)
{
	__pid_t	pid;
	int		status;

	if (!line->args || !*line->args)
		return (0);
	if (is_fork == 0)
	{
		pid = fork();
		if (pid < 0)
		{
			free_line_struct(line, 1);
			ft_lstclear_var(&lst_var, free);
			exit(EXIT_FAILURE);
		}
		if  (pid == 0)
			exec_process(line, lst_var, dir);
		else
			waitpid(-1, &status, 0);
	}
	else
		exec_process(line, lst_var, dir);
	return (0);
}
