/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:19:28 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/13 17:57:11 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ft_free_tab(char **tab, int line)
{
	while (line > 0)
	{
		line--;
		free(*(tab + line));
	}
	free(tab);
	return (NULL);
}

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
	int		size_content;
	int		size_tab;
	int		i;

	if (!env || !*env || !tab)
		return (NULL);
	content = NULL;
	size_tab = ft_strlen(tab);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], tab, size_tab) == 0)
		{
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

int	fill_tab(char **env, const char *s, char *tab, int *j)
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

char	*ft_substr_variable(char **env, char const *s, int i, int j, int end)
{
	int		count;
	char	*tab;

	if (!s)
		return (NULL);
	(void)env;
	count = 0;
	while (i < end)
	{
		if (s[i] == '$' && (s[i + 1] == '_' || ft_isalpha(s[i + 1])))
			count += get_count(env, s + i + 1, &i);
		else
			count++;
		i++;
	}
	tab = (char *)malloc(sizeof(char) * (count + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < end)
	{
		if (s[i] == '$' && (s[i + 1] == '_' || ft_isalpha(s[i + 1])))
			i += fill_tab(env, s + i + 1, tab, &j) + 1;
		else
			tab[j++] = s[i++];
	}
	tab[j] = '\0';
	return (tab);
}

static char	**ft_add_lines(char **env, char **tab, char const *s, char c, int line)
{
	int	i;

	while (*s)
	{
		while (*s && *s == c)
			s++;
		if ((*s == '"' || *s == '\'') && c == ' ')
			c = *s;
		i = 0;
		while (*s && *s != c)
			s += (i++ >= 0);
		if (i > 0)
		{
			if (c != '\'')
				*(tab + line) = ft_substr_variable(env, s - i, 0, 0, i);
			else
				*(tab + line) = ft_substr(s - i, 0, i);
			if (*(tab + line) == NULL)
				ft_free_tab(tab, line);
			if (!tab)
				return (NULL);
			line++;
			while (*s && *s == c)
				s++;
			c = ' ';
		}
	}
	return (tab);
}

char	**ft_split_line(char **env, char const *s, char c, unsigned int line, int i)
{
	char	**tab;

	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && c == ' ')
			c = s[i];
		if (s[i] != c)
		{
			line++;
			while (s[i] && s[i] != c)
				i++;
			c = ' ';
		}
		else
			i++;
	}
	tab = (char **)malloc(sizeof(char *) * (line + 1));
	if (!tab)
		return (NULL);
	tab = ft_add_lines(env, tab, s, ' ', 0);
	if (!tab)
		return (NULL);
	*(tab + line) = NULL;
	return (tab);
}
