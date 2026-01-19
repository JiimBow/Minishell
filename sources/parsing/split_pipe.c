/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:16:08 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/19 16:18:14 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_word(char *line, int i)
{
	char	quote;

	while (line[i] && line[i] != '|')
	{
		if (is_quote(line[i]))
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
		}
		i++;
	}
	return (i);
}

static char	**ft_add_lines(char *line, int row)
{
	char	**tab;
	int		save_i;
	int		i;

	tab = (char **)malloc(sizeof(char *) * (row + 1));
	if (!tab)
		return (NULL);
	tab[row] = NULL;
	i = 0;
	row = 0;
	while (line[i])
	{
		while (line[i] && is_spaces(line[i]))
			i++;
		save_i = i;
		i = parse_word(line, i);
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
		if (line[i])
			i++;
	}
	return (tab);
}

char	**split_pipe(char *line)
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
		while (line[i] && is_spaces(line[i]))
			i++;
		save_i = i;
		i = parse_word(line, i);
		if (i > save_i)
			row++;
		if (line[i])
			i++;
	}
	tab = ft_add_lines(line, row);
	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		printf("block[%d]=%s\n", i, tab[i]);
		i++;
	}
	return (tab);
}
