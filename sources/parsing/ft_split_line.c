/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:19:28 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/14 11:42:14 by mgarnier         ###   ########.fr       */
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

static char	**ft_add_lines(char **env, char **tab, char const *s, char c)
{
	int	i;
	int	line;

	line = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t' || *s == '\n'))
			s++;
		if (*s == '"' || *s == '\'')
			c = *s++;
		i = 0;
		while (*s && *s != c)
		{
			if (c == ' ' && (*s == '\t' || *s == '\n'))
				break ;
			s += (i++ >= 0);
		}
		if (i > 0)
		{
			if (c != '\'')
				*(tab + line) = ft_substr_variable(env, s - i, 0, i);
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

char	**ft_split_line(char **env, char const *s, char c, int line)
{
	char	**tab;
	int		i;

	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
			i++;
		if (s[i] == '"' || s[i] == '\'')
			c = s[i++];
		if (s[i] != c)
		{
			line++;
			while (s[i] && s[i] != c)
			{
				if (c == ' ' && (s[i] == '\t' || s[i] == '\n'))
					break ;
				i++;
			}
			if (s[i] != '\0')
				i++;
			c = ' ';
		}
		else
			i++;
	}
	tab = (char **)malloc(sizeof(char *) * (line + 1));
	if (!tab)
		return (NULL);
	tab = ft_add_lines(env, tab, s, ' ');
	if (!tab)
		return (NULL);
	*(tab + line) = NULL;
	return (tab);
}
