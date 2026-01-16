/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:06:53 by jodone            #+#    #+#             */
/*   Updated: 2026/01/16 13:17:29 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static int	env_size(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env && env[i])
// 		i++;
// 	return (i);
// }

// static char	**new_env(char **env, int index_supp)
// {
// 	char	**n_env;
// 	int		env_len;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	env_len = env_size(env);
// 	n_env = ft_calloc(env_len, sizeof(char *));
// 	while (i < env_len)
// 	{
// 		if (i == index_supp)
// 			i++;
// 		n_env[j] = ft_strdup(env[i]);
// 		i++;
// 		j++;
// 	}
// 	n_env[j] = NULL;
// 	free_double_tab(env);
// 	return (n_env);
// }

static void	remove_node(t_var *current_lst)
{
	t_var	*supp;

	supp = current_lst->next;
	current_lst->next = supp->next;
	free(supp->name);
	free(supp->content);
	free(supp);
}

static void	remove_var(t_var **lst_var, char *name)
{
	t_var	*tmp;
	int		len_name;

	tmp = *lst_var;
	len_name = ft_strlen(name);
	while (tmp)
	{
		if (tmp->next)
		{
			if (ft_strncmp(name, tmp->next->name, len_name + 1) == 0)\
			{
				remove_node(tmp);
				break ;
			}
		}
		tmp = tmp->next;
	}
}

int	ft_unset(t_line *line, t_var **lst_var)
{
	int	i;

	i = 1;
	while (line->args[i])
	{
		remove_var(lst_var, line->args[i]);
		i++;
	}
	return (0);
}
