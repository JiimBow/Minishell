/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:19:28 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/09 11:03:51 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	**ft_add_lines(char **tab, char const *s, char c, int line)
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

char	**ft_split_line(char const *s, char c, unsigned int line, int i)
{
	char			**tab;

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
	tab = ft_add_lines(tab, s, ' ', 0);
	if (!tab)
		return (NULL);
	*(tab + line) = NULL;
	return (tab);
}
