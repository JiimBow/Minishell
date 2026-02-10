/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 11:55:03 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/10 12:12:53 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_words(char *s, int *i)
{
	char	quote;
	int		row;

	row = 0;
	if (!is_quote(s[*i]))
	{
		row++;
		while (s[*i] && !is_quote(s[*i]))
			(*i)++;
	}
	else
	{
		quote = s[(*i)++];
		row++;
		while (s[*i] && s[*i] != quote)
			(*i)++;
		if (s[*i])
			(*i)++;
	}
	return (row);
}

static char	**ft_add_lines(char **tab, char *line)
{
	int	save_i;
	int	row;
	int	i;

	i = 0;
	row = 0;
	while (line && line[i])
	{
		save_i = i;
		find_words(line, &i);
		if (i > save_i)
		{
			tab[row] = ft_substr(line + save_i, 0, i - save_i);
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

char	**split_words(char *s)
{
	char	**tab;
	int		row;
	int		i;

	i = 0;
	row = 0;
	while (s && s[i])
		row += find_words(s, &i);
	tab = (char **)malloc(sizeof(char *) * (row + 1));
	if (!tab)
		return (NULL);
	tab[row] = NULL;
	tab = ft_add_lines(tab, s);
	return (tab);
}
