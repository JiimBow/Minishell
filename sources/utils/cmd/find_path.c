/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:53:10 by jodone            #+#    #+#             */
/*   Updated: 2026/01/29 18:31:12 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	return (i);
}

static char	*join_path(char *dir, char *cmd)
{
	char	*result;
	int		len_dir;
	int		len_path;

	len_dir = ft_strlen(dir);
	len_path = len_dir + ft_strlen(cmd) + 1;
	result = malloc((len_path + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, dir, len_dir + 1);
	ft_strlcat(result, "/", len_dir + 2);
	ft_strlcat(result, cmd, len_path + 1);
	return (result);
}

static int	cmd_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*find_cmd_path(t_line *line, char **paths, int i, char *full_path)
{
	if (cmd_check(line->args[0]) == 1)
	{
		full_path = ft_strdup(line->args[0]);
		return (full_path);
	}
	i = find_envp(line->env);
	if (line->env && line->env[i] && line->args[0])
	{
		paths = ft_split(line->env[i] + 5, ':');
		i = 0;
		while (paths && paths[i])
		{
			full_path = join_path(paths[i++], line->args[0]);
			if (access(full_path, X_OK) == 0)
				break ;
			free(full_path);
			full_path = NULL;
		}
		free_double_tab(paths);
	}
	else
		full_path = ft_strdup("fail");
	return (full_path);
}
