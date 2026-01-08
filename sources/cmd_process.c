/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:24:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/08 12:00:53 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	exec_process(char *cmd, char **envp)
{
	char	*path_cmd;
	char	*full_path;
	char	**arg_cmd;

	full_path = NULL;
	arg_cmd = ft_split(cmd, ' ');
	printf("%s\n", arg_cmd[0]);
	printf("%s\n", arg_cmd[1]);
	if (!arg_cmd || !arg_cmd[0])
	{
		perror(cmd);
		if (arg_cmd)
			pointer_free(arg_cmd);
		exit(127);
	}
	path_cmd = find_path(arg_cmd[0], envp, 0, full_path);
	if (!path_cmd || execve(path_cmd, arg_cmd, envp) == -1)
	{
		perror(arg_cmd[0]);
		pointer_free(arg_cmd);
		free(path_cmd);
		exit(127);
	}
}

void	process(char *cmd, char **envp)
{
	__pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		exec_process(cmd, envp);
	waitpid(-1, &status, 0);
}
