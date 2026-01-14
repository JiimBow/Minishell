/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:41:42 by jodone            #+#    #+#             */
/*   Updated: 2026/01/14 19:17:57 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*fill_env(char *name, char *content)
{
	char	*env;
	int		len_name;
	int		len_content;

	len_name = ft_strlen(name);
	len_content = ft_strlen(content);
	env = ft_calloc(len_name + len_content + 2, sizeof(char));
	ft_strlcpy(env, name, len_name + 1);
	ft_strlcat(env, "=", len_name + 2);
	ft_strlcat(env, content, len_name + len_content + 2);
	return (env);
}

static char	**ft_copy_env(t_var **lst_var)
{
	char	**env;
	int		i;
	t_var	*tmp;

	// while (envp[i])
	// 	i++;
	// env = ft_calloc((i + 1), sizeof(char *));
	// if (!env)
	// 	return (NULL);
	// i = 0;
	// while (envp[i])
	// {
	// 	env[i] = ft_strdup(envp[i]);
	// 	i++;
	// }
	i = 0;
	tmp = *lst_var;
	env = ft_calloc(ft_lstsize_var(tmp), sizeof(char *));
	while (tmp)
	{
		env[i] = fill_env(tmp->name, tmp->content);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

t_env	*ft_get_env(t_var **lst_var)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->env = ft_copy_env(lst_var);
	return (env);
}
