/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:24:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/29 18:44:38 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_error(t_line *line, char *path_cmd)
{
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
			write_error(line->args[0], 3);
			free_line_struct(line, 1);
			exit(126);
		}
		exec_error(line, path_cmd);
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

static int	process(t_line *line, t_var *lst_var, int is_fork)
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

void	assignement(t_line *line, t_var *lst_var, int is_fork)
{
	if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "cd", 3) == 0)
		line->sig = ft_cd(line, lst_var);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "pwd", 4) == 0)
		line->sig = ft_pwd(lst_var);
	else if (line->args && line->args[0] && !line->args[1]
		&& ft_strncmp(line->args[0], "env", 4) == 0)
		line->sig = ft_env(line->env);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "echo", 5) == 0)
		line->sig = ft_echo(line->args);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "unset", 6) == 0)
		line->sig = ft_unset(line, &lst_var);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "exit", 5) == 0)
		line->sig = free_before_exit(line, lst_var);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "export", 7) == 0)
		line->sig = ft_export(line, &lst_var, line->args);
	else if (line->args)
		line->sig = process(line, lst_var, is_fork);
}
