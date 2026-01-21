/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:24:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/21 17:13:33 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(char *cmd_name, int code)
{
	if (code == 1)
	{
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": command not found\n", 20);
	}
	if (code == 2)
	{
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": No such file or directory\n", 28);
	}
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

static void	exec_process(t_line *line, t_var *lst_var, int is_dir)
{
	char	*path_cmd;
	char	*full_path;
	char	**paths;

	paths = NULL;
	full_path = NULL;
	path_cmd = find_cmd_path(line, paths, 0, full_path);
	if (!path_cmd || execve(path_cmd, line->args, line->env) == -1
		|| is_dir == 1)
	{
		ft_lstclear_var(&lst_var, free);
		free(path_cmd);
		if (is_dir == 1)
		{
			perror(line->args[0]);
			free_line_struct(line, 1);
			exit(126);
		}
		if (!path_cmd)
			write_error(line->args[0], 1);
		else
			write_error(line->args[0], 2);
		free_line_struct(line, 1);
		exit(127);
	}
}

int	process(t_line *line, t_var *lst_var, int dir, int is_fork)
{
	__pid_t	pid;
	int		status;

	status = 0;
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
		if (pid == 0)
			exec_process(line, lst_var, dir);
		else
			waitpid(-1, &status, 0);
	}
	else
		exec_process(line, lst_var, dir);
	return (return_value(status));
}
