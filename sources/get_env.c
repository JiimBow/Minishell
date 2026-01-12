/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:41:42 by jodone            #+#    #+#             */
/*   Updated: 2026/01/12 14:08:15 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*ft_get_env(t_env *env, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = ft_calloc((i + 1), sizeof(char*));
	i = 0;
	while (envp[i])
	{
		env->env[i] = ft_strdup(envp[i]);
		i++;
	}
	env->env[i] = NULL;
	return (env);
}
