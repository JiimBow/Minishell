/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:59:27 by jodone            #+#    #+#             */
/*   Updated: 2026/01/16 23:30:05 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_no_path(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror(NULL);
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}

int	ft_pwd(t_line *env)
{
	char	*path;
	int		i;

	i = 0;
	path = get_env_path("PWD", env->env, &i);
	if (!path)
	{
		if (if_no_path() == 0)
			return (0);
		return (1);
	}
	else
		printf("%s\n", path);
	return (0);
}
