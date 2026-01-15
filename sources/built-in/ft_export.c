/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:10:11 by jodone            #+#    #+#             */
/*   Updated: 2026/01/15 17:44:23 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	var_exist(t_var **lst_var, char *name, char *content, int update)
{
	t_var	*tmp;
	
	tmp = *lst_var;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
		{
			if (update && content)
			{
				tmp->content = ft_strdup(content);
				return (0);
			}
			else
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	add_var(t_var **lst_var, char *arg)
{
	int		i;
	char	*name;
	char	*content;

	i = 0;
	content = NULL;
	while (arg[i] && arg[i] != '=')
		i++;
	name = ft_substr(arg, 0, i);
	if (ft_strchr(arg, '='))
	{
		while (arg[i] != '=')
			i++;
		content = ft_substr(arg, i + 1, ft_strlen(arg) - i);
	}
	if (var_exist(lst_var, name, content, 0))
		var_exist(lst_var, name, content, 1);
	else
		ft_lstadd_back_var(lst_var, ft_lst_new_var(name, content));
	if (content)
		free(content);
	free(name);
}

int	ft_export(t_var **lst_var, char **args)
{
	int		i;

	if (!args[1])
	{
		if (!already_sorted(lst_var))
		{
			reset_rank(lst_var);
			rank_var(lst_var);
		}
		display_export(lst_var);
	}
	else if ((!ft_isalpha(args[1][0]) && args[1][0] != '_'))
	{
		write(2, "minishell: export: not a valid identifier\n", 42);
		return (1);
	}
	else
	{
		i = 1;
		while (args[i])
			add_var(lst_var, args[i++]);
	}
	return (0);
}
