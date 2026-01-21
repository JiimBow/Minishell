/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:19:28 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/21 22:30:04 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_word(char *line, int i)
{
	char	quote;

	while (line[i] && !is_spaces(line[i]))
	{
		while (line[i] && !is_spaces(line[i]) && !is_quote(line[i]))
			i++;
		if (is_quote(line[i]))
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			i++;
		}
	}
	return (i);
}

static char	*substr_unquote(char const *s, int n)
{
	char	*new;
	char	quote;
	int		i;
	int		j;

	new = ft_calloc(sizeof(char), n + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n)
	{
		if (is_quote(s[i]))
		{
			quote = s[i++];
			while (i < n && s[i] != quote)
				new[j++] = s[i++];
			i++;
		}
		else
			new[j++] = s[i++];
	}
	new[j] = '\0';
	return (new);
}

static char	**ft_add_lines(char **tab, char *line, int i, int row)
{
	int		save_i;

	while (line[i])
	{
		i = skip_spaces(line, i);
		save_i = i;
		i = parse_word(line, i);
		if (i > save_i)
		{
			if (row > 0 && tab[row - 1][0] && tab[row - 1][1]
				&& tab[row - 1][0] == '<' && tab[row - 1][1] == '<')
				tab[row] = ft_substr(line + save_i, 0, i - save_i);
			else
				tab[row] = substr_unquote(line + save_i, i - save_i);
			if (!tab[row])
			{
				ft_free_tab(tab, row);
				return (NULL);
			}
			row++;
		}
	}
	return (tab);
}

char	**split_line(char *line)
{
	char	**tab;
	int		save_i;
	int		row;
	int		i;

	i = 0;
	row = 0;
	if (!line)
		return (NULL);
	while (line[i])
	{
		i = skip_spaces(line, i);
		save_i = i;
		i = parse_word(line, i);
		if (i > save_i)
			row++;
	}
	tab = (char **)malloc(sizeof(char *) * (row + 1));
	if (!tab)
		return (NULL);
	tab[row] = NULL;
	tab = ft_add_lines(tab, line, 0, 0);
	return (tab);
}
