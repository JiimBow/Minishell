/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:36:41 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/23 11:59:12 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(const char *s)
{
	char	*name;
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	name = (char *)malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

char	*get_content(char **env, char *tab)
{
	char	*content;
	int		size_tab;
	int		i;

	if (!env || !tab)
		return (NULL);
	size_tab = ft_strlen(tab);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], tab, size_tab) == 0 && env[i][size_tab] == '=')
		{
			content = ft_strdup(env[i] + size_tab + 1);
			return (content);
		}
		i++ ;
	}
	return (NULL);
}

int	get_count(char **env, const char *s, int *i)
{
	char	*name;
	char	*content;
	int		count;

	if (!env || !*env || !s)
		return (0);
	count = 0;
	name = get_name(s);
	content = get_content(env, name);
	if (content)
	{
		count = ft_strlen(content);
		*i += ft_strlen(name);
	}
	free(name);
	free(content);
	return (count);
}

int	get_size_with_variable(t_line *line, const char *s, int count, int i)
{
	char	quote;

	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote = s[i++];
			count += 2;
			while (s[i] != quote)
			{
				if (quote == '"' && s[i] == '$' && s[i + 1])
					count += variable_size(line, s, &i, 0);
				else
					count++;
				i++;
			}
		}
		else if (s[i] == '$' && s[i + 1])
			count += variable_size(line, s, &i, 0);
		else
			count++;
		i++;
	}
	return (count);
}
