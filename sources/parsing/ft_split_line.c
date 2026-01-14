/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:19:28 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/14 23:38:15 by mgarnier         ###   ########.fr       */
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

static int	is_spaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

static int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

static char	**ft_add_lines(char **env, char const *reader, int line)
{
	char	**tab;
	char	quote;
	int		start;
	int		i;

	tab = (char **)malloc(sizeof(char *) * (line + 1));
	if (!tab)
		return (NULL);
	tab[line] = NULL;
	i = 0;
	line = 0;
	while (reader[i])
	{
		while (reader[i] && is_spaces(reader[i]))
			i++;
		start = i;
		while (reader[i] && !is_spaces(reader[i]))
		{
			while (reader[i] && !is_spaces(reader[i]) && !is_quote(reader[i]))
				i++;
			if (is_quote(reader[i]))
			{
				quote = reader[i++];
				while (reader[i++] != quote)
					;
			}
		}
		if (i > start)
		{
			tab[line] = ft_substr_variable(env, reader + start, 0, i - start);
			if (!tab[line])
			{
				ft_free_tab(tab, line);
				return (NULL);
			}
			line++;
		}
	}
	return (tab);
}

char	**ft_split_line(char **env, char const *reader)
{
	char	**tab;
	char	quote;
	int		check;
	int		line;
	int		i;

	i = 0;
	line = 0;
	while (reader[i])
	{
		check = 0;
		while (reader[i] && is_spaces(reader[i]))
			i++;
		while (reader[i] && !is_spaces(reader[i]))
		{
			while (reader[i] && !is_spaces(reader[i]) && !is_quote(reader[i]))
			{
				check = 1;
				i++;
			}
			if (is_quote(reader[i]))
			{
				check = 1;
				quote = reader[i++];
				while (reader[i++] != quote)
					;
			}
		}
		if (check == 1)
			line++;
	}
	tab = ft_add_lines(env, reader, line);
	if (!tab)
		return (NULL);
	return (tab);
}
