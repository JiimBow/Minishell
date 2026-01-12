/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:24:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/12 16:30:14 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	exec_process(char **cmd, t_env *env)
{
	char	*path_cmd;
	char	*full_path;

	full_path = NULL;
	path_cmd = find_path(cmd[0], env->env, 0, full_path);
	if (!path_cmd || execve(path_cmd, cmd, env->env) == -1)
	{
		perror(cmd[0]);
		pointer_free(cmd);
		free(path_cmd);
		free_double_tab(env->env);
		free(env);
		exit(127);
	}
}

void	process(char **cmd, t_env *env)
{
	__pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		exec_process(cmd, env);
	waitpid(-1, &status, 0);
}
