/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:06:53 by jodone            #+#    #+#             */
/*   Updated: 2026/01/13 11:40:42 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**new_env(char **env)
{
	
}

void	ft_unset(t_env *env, char **args)
{
	int	i;
	int	env_index;

	i = 1;
	while (args[i])
	{
		env_index = 0;
		if (get_env_path(args[i], env->env, &env_index))
			free(env->env[env_index]);
		i++;
	}
}
