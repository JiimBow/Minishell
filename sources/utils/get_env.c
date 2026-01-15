/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 13:41:42 by jodone            #+#    #+#             */
/*   Updated: 2026/01/15 11:02:28 by jodone           ###   ########.fr       */
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

char	**ft_copy_env(t_var **lst_var)
{
	char	**env;
	int		i;
	t_var	*tmp;

	i = 0;
	tmp = *lst_var;
	env = ft_calloc(ft_lstsize_var(tmp) + 1, sizeof(char *));
	while (tmp)
	{
		if (tmp->name && tmp->content)
		{
			env[i] = fill_env(tmp->name, tmp->content);
			i++;	
		}
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

t_env	*ft_get_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->env = NULL;
	return (env);
}
