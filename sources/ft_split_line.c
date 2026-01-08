/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:19:28 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/08 10:49:35 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		i = 0;
		while (*s && *s != c)
		{
			s++;
			i++;
		}
		if (i > 0)
		{
			*(tab + line) = ft_substr(s - i, 0, i);
			line++;
		}
		if (i > 0 && !*(tab + line - 1))
		{
			ft_free_tab(tab, line);
			return (NULL);
		}
	}
	*(tab + line) = NULL;
	return (tab);
}

char	**ft_split_line(char const *s, char c)
{
	char			**tab;
	int				i;
	unsigned int	line;

	i = 0;
	line = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			line++;
		i++;
	}
	tab = (char **)malloc(sizeof(char *) * (line + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tab = ft_add_lines(tab, s, c, i);
	if (!tab)
		return (NULL);
	*(tab + line) = NULL;
	return (tab);
}