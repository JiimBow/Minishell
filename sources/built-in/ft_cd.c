/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:44:39 by jodone            #+#    #+#             */
/*   Updated: 2026/01/14 15:33:28 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_path(char *str, char **envp, int *i)
{
	int	path_len;

	path_len = ft_strlen(str);
	while (envp && envp[(*i)])
	{
		if (ft_strncmp(envp[(*i)], str, path_len) == 0)
			return (envp[(*i)] + path_len + 1);
		(*i)++;
	}
	return (NULL);
}

void	update_path(char **envp, int *i, int is_old)
{
	char	curr_path[PATH_MAX];
	char	*new_path;
	int		path_len;

	(*i) = 0;
	getcwd(curr_path, sizeof(curr_path));
	path_len = ft_strlen(curr_path);
	if (is_old == 1)
	{
		get_env_path("OLDPWD", envp, i);
		new_path = malloc((7 + ft_strlen(curr_path) + 1) * sizeof(char));
		ft_strlcpy(new_path, "OLDPWD=", 8);
		ft_strlcat(new_path, curr_path, path_len + 9);
		free(envp[(*i)]);
		envp[(*i)] = ft_strdup(new_path);
		free(new_path);
	}
	else
	{
		get_env_path("PWD", envp, i);
		new_path = malloc((4 + ft_strlen(curr_path) + 1) * sizeof(char));
		ft_strlcpy(new_path, "PWD=", 5);
		ft_strlcat(new_path, curr_path, path_len + 6);
		free(envp[(*i)]);
		envp[(*i)] = ft_strdup(new_path);
		free(new_path);
	}
}

int	ft_cd(char **argv, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	if (argv[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	if (!argv[1] || ft_strncmp(argv[1], "~", 2) == 0)
		path = get_env_path("HOME", envp, &i);
	else
		path = argv[1];
	update_path(envp, &i, 1);
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		perror(path);
		return (1);
	}
	update_path(envp, &i, 0);
	return (0);
}
