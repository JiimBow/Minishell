/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:44:39 by jodone            #+#    #+#             */
/*   Updated: 2026/01/09 10:48:45 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/minishell.h"
char	*get_path(char *str, char **envp)
{
	int	i;
	int	path_len;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], str, path_len) == 0)
			return (envp[i] + path_len + 1);
		i++;
	}
	return (NULL);
}

int	ft_cd(char **argv, char **envp)
{
	char	*path;

	if (!argv[1] || argv[1] == '~')
		path = get_path("HOME", envp);
	else if (argv[1] == '-')
		path = get_path("OLDPWD", envp);
	else
		path = argv[1];
	// remplacer le OLDPWD
	if (chdir(path) == -1)
	{
		perror(path);
		return (1);
	}
	// mettre a jour le PWD
	return (0);
}
