/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:59:27 by jodone            #+#    #+#             */
/*   Updated: 2026/01/14 12:00:56 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	if_no_path(void)
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

int	ft_pwd(t_env *env)
{
	char	*path;
	int		i;

	i = 0;
	// while (env->env[i])
	// {
	// 	if (ft_strncmp(env->env[i], "PWD=", 4) == 0)
	// 	{
	// 		printf("%s\n", env->env[i] + 4);
	// 		return (0);
	// 	}
	// 	i++;
	// }
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
