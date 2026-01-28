/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:38:33 by jodone            #+#    #+#             */
/*   Updated: 2026/01/28 15:58:11 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *line)
{
	int		len_name;
	char	*name;

	if (!line)
		return (NULL);
	len_name = 0;
	while (line[len_name] && line[len_name] != '=')
		len_name++;
	if (len_name == 0)
		return (NULL);
	if (line[len_name - 1] == '+')
	{
		name = ft_calloc(len_name, sizeof(char));
		if (!name)
			return (NULL);
		ft_strlcpy(name, line, len_name);
	}
	else
	{
		name = ft_calloc(len_name + 1, sizeof(char));
		if (!name)
			return (NULL);
		ft_strlcpy(name, line, len_name + 1);
	}
	return (name);
}

static char	*get_env_content(char *line)
{
	int		len_content;
	int		i;
	int		start;
	char	*content;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	len_content = 0;
	start = i + 1;
	while (line[++i])
		len_content++;
	content = ft_calloc(len_content + 1, sizeof(char));
	if (!content)
		return (NULL);
	ft_strlcpy(content, line + start, len_content + 1);
	return (content);
}

t_var	*get_var(char **envp)
{
	t_var	*lst_var;
	int		i;
	char	*name;
	char	*content;

	i = 0;
	lst_var = NULL;
	while (envp[i])
	{
		name = get_env_name(envp[i]);
		if (!name)
			error_memory_failed(NULL, lst_var);
		content = get_env_content(envp[i]);
		if (!content)
		{
			free(name);
			error_memory_failed(NULL, lst_var);
		}
		ft_lstadd_back_var(&lst_var, ft_lst_new_var(name, content, -1));
		free(name);
		free(content);
		i++;
	}
	return (lst_var);
}
