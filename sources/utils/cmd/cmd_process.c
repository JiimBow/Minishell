/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:24:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/29 14:32:00 by mgarnier         ###   ########.fr       */
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
		write(2, "minishell: ", 11);
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

static void	exec_process(t_line *line, t_var *lst_var)
{
	char	*path_cmd;
	char	*full_path;
	char	**paths;

	paths = NULL;
	full_path = NULL;
	path_cmd = find_cmd_path(line, paths, 0, full_path);
	if (!path_cmd || execve(path_cmd, line->args, line->env) == -1
		|| line->is_dir == 1)
	{
		ft_lstclear_var(&lst_var, free);
		free(path_cmd);
		if (line->is_dir == 1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(line->args[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			free_line_struct(line, 1);
			exit(126);
		}
		if (!path_cmd)
			write_error(line->args[0], 1);
		else if (ft_strncmp(line->args[0], ".", 2) == 0)
		{
			ft_putstr_fd("minishell: .: filename argument required\n", 2);
			free_line_struct(line, 1);
			exit(2);
		}
		else
			write_error(line->args[0], 2);
		free_line_struct(line, 1);
		exit(127);
	}
}

int	verif_if_first_argument_is_dir(t_line *line)
{
	struct stat	verif;

	if (stat(line->args[0], &verif) != 0
		|| !ft_strchr(line->args[0], '/'))
		return (0);
	if (S_ISDIR(verif.st_mode))
		return (1);
	return (0);
}

int	process(t_line *line, t_var *lst_var, int is_fork)
{
	__pid_t	pid;
	int		status;

	status = 0;
	if (!line->args || !*line->args)
		return (0);
	line->is_dir = verif_if_first_argument_is_dir(line);
	if (is_fork == 0)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		if (pid == 0)
			exec_process(line, lst_var);
		else
			waitpid(-1, &status, 0);
	}
	else
		exec_process(line, lst_var);
	return (return_value(status));
}
