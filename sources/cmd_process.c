/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:24:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/08 16:27:29 by mgarnier         ###   ########.fr       */
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

void	exec_process(char **cmd, char **envp)
{
	char	*path_cmd;
	char	*full_path;

	full_path = NULL;
	path_cmd = find_path(cmd[0], envp, 0, full_path);
	if (!path_cmd || execve(path_cmd, cmd, envp) == -1)
	{
		perror(cmd[0]);
		pointer_free(cmd);
		free(path_cmd);
		exit(127);
	}
}

void	process(char **cmd, char **envp)
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
