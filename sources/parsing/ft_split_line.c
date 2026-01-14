/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:19:28 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/14 15:54:04 by mgarnier         ###   ########.fr       */
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

static char	**ft_add_lines(char **env, char **tab, char const *s, char sep)
{
	int	i;
	int	line;

	line = 0;
	while (*s)
	{
		while (*s && (*s == ' ' || *s == '\t' || *s == '\n'))
			s++;
		if (*s == '"' || *s == '\'')
			sep = *s++;
		i = 0;
		while (*s && *s != sep)
		{
			if (sep == ' ' && (*s == '\t' || *s == '\n'))
				break ;
			if (*s == '"' || *s == '\'')
			{
				sep = *s++;
				while (*s && *s != sep)
					s += (i++ >= 0);
				sep = ' ';
			}
			else
				s += (i++ >= 0);
		}
		if (i > 0)
		{
			tab[line] = ft_substr_variable(env, s - i, i, sep);
			if (!tab[line])
			{
				ft_free_tab(tab, line);
				return (NULL);
			}
			line++;
			if (*s)
				s++;
			sep = ' ';
		}
	}
	return (tab);
}

char	**ft_split_line(char **env, char const *s, char sep, int line)
{
	char	**tab;
	int		i;

	i = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
			i++;
		if (s[i] == '"' || s[i] == '\'')
			sep = s[i++];
		if (s[i] != sep)
		{
			line++;
			while (s[i] && s[i] != sep)
			{
				if (sep == ' ' && (s[i] == '\t' || s[i] == '\n'))
					break ;
				if (s[i] == '"' || s[i] == '\'')
				{
					sep = s[i++];
					while (s[i] && s[i] != sep)
						i++;
					sep = ' ';
				}
				i++;
			}
			if (s[i] != '\0')
				i++;
			sep = ' ';
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
