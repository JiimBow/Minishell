/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:10:11 by jodone            #+#    #+#             */
/*   Updated: 2026/02/10 11:05:03 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_exist(t_var **lst_var, char *name, char *content, int update)
{
	t_var	*tmp;

	tmp = *lst_var;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name) + 1) == 0)
		{
			if (update && content)
			{
				free(tmp->content);
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

static char	*content_cat(t_var **lst_var, char *name, char *content)
{
	t_var	*tmp;
	char	*new_content;

	tmp = *lst_var;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, ft_strlen(name)) == 0)
		{
			new_content = ft_strjoin(tmp->content, content);
			free(content);
			return (new_content);
		}
		tmp = tmp->next;
	}
	new_content = ft_strdup(content);
	free(content);
	return (new_content);
}

static void	add_var(t_var **lst_var, char *arg, char *name)
{
	int		i;
	char	*content;

	i = 0;
	content = NULL;
	if (!name)
		return ;
	if (ft_strchr(arg, '='))
	{
		while (arg[i] != '=')
			i++;
		content = ft_substr(arg, i + 1, ft_strlen(arg) - i);
		if (arg[i - 1] == '+')
			content = content_cat(lst_var, name, content);
	}
	if (var_exist(lst_var, name, content, 0))
		var_exist(lst_var, name, content, 1);
	else
		ft_lstadd_back_var(lst_var, ft_lst_new_var(name, content, -1));
	if (content)
		free(content);
}

int	ft_export(t_line *line, t_var **lst_var, char **args)
{
	int		i;
	char	*name;

	line->sig = 0;
	if (!args[1])
	{
		if (!already_sorted(lst_var))
			rank_var(lst_var);
		display_export(lst_var);
	}
	else
	{
		i = 1;
		while (args[i])
		{
			name = get_env_name(args[i]);
			if (!parse_export(name, args[i]))
				line->sig = 1;
			add_var(lst_var, args[i++], name);
			free(name);
		}
	}
	return (line->sig);
}
