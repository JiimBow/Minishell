/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:38:33 by jodone            #+#    #+#             */
/*   Updated: 2026/01/16 23:29:12 by mgarnier         ###   ########.fr       */
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
	name = ft_calloc(len_name + 1, sizeof(char));
	ft_strlcpy(name, line, len_name + 1);
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
	ft_strlcpy(content, line + start, len_content + 1);
	return (content);
}

void	get_var(t_var **lst_var, char **envp)
{
	int		i;
	char	*name;
	char	*content;

	i = 0;
	while (envp[i])
	{
		name = get_env_name(envp[i]);
		content = get_env_content(envp[i]);
		ft_lstadd_back_var(lst_var, ft_lst_new_var(name, content));
		free(name);
		free(content);
		i++;
	}
}
