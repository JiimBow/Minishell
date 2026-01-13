/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:06:53 by jodone            #+#    #+#             */
/*   Updated: 2026/01/13 13:53:06 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

char	**new_env(char **env, int index_supp)
{
	char	**n_env;
	int		env_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env_len = env_size(env);
	n_env = ft_calloc(env_len, sizeof(char *));
	while (i < env_len)
	{
		if (i == index_supp)
			i++;
		n_env[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	n_env[j] = NULL;
	free_double_tab(env);
	return (n_env);
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
		{
			env->env = new_env(env->env, env_index);
			break ;
		}
		i++;
	}
}
