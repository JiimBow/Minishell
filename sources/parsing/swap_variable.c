/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:59:24 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/14 23:45:37 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name(const char *s)
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

static char	*get_content(char **env, char *tab)
{
	char	*content;
	int		size_content;
	int		size_tab;
	int		i;
	int		j;

	if (!env || !*env || !tab)
		return (NULL);
	content = NULL;
	size_tab = ft_strlen(tab);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], tab, size_tab) == 0)
		{
			j = 0;
			while (env[i][j] && tab[j] && env[i][j] != '=')
				j++;
			if (env[i][j] != '=')
				return (NULL);
			size_content = ft_strlen(env[i]) - (size_tab + 1);
			content = ft_calloc(sizeof(char), size_content + 1);
			if (!content)
				return (NULL);
			ft_strlcpy(content, env[i] + size_tab + 1, size_content + 1);
			break ;
		}
		i++;
	}
	return (content);
}

static int	get_count(char **env, const char *s, int *i)
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

static int	fill_tab(char **env, const char *s, char *tab, int *j)
{
	char	*name;
	char	*content;
	int		n;

	if (!env || !*env || !tab)
		return (0);
	name = get_name(s);
	content = get_content(env, name);
	n = 0;
	while (content && content[n])
		tab[(*j)++] = content[n++];
	n = ft_strlen(name);
	free(name);
	free(content);
	return (n);
}

static int	add_variable(char **env, const char *s, int *i, int count)
{
	char	*tmp;

	if (s[*i + 1] == '?')
	{
		tmp = ft_itoa(sig);
		count = ft_strlen(tmp);
		free(tmp);
		(*i)++;
	}
	else if (s[*i + 1] == '_' || ft_isalpha(s[*i + 1]))
		count = get_count(env, s + *i + 1, i);
	else
		count = 1;
	return (count);
}

char	*ft_substr_variable(char **env, char const *s, int i, int n)
{
	char	*tab;
	char	*tmp;
	int		count;
	int		j;

	if (!env || !*env || !s)
		return (NULL);
	count = 0;
	while (i < n)
	{
		if (s[i] == '$' && s[i + 1])
			count += add_variable(env, s, &i, 0);
		else
			count++;
		i++;
	}
	tab = ft_calloc(sizeof(char), (count + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n)
	{
		if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
		{
			tmp = ft_itoa(sig);
			count = 0;
			while (tmp[count])
				tab[j++] = tmp[count++];
			i += 2;
			free(tmp);
		}
		else if (s[i] == '$' && s[i + 1] && (s[i + 1] == '_' || ft_isalpha(s[i + 1])))
			i += fill_tab(env, s + i + 1, tab, &j) + 1;
		else if (s[i] == '\'' || s[i] == '"')
			i++;
		else
			tab[j++] = s[i++];
	}
	return (tab);
}
