/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:24:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/08 11:24:34 by jodone           ###   ########.fr       */
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
	if (!arg_cmd || !arg_cmd[0])
	{
		perror(cmd);
		
	}
}

void	process(char *cmd, char **envp)
{
	__pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
		exec_process;
	else
	b45467f
	38ca2af
}
