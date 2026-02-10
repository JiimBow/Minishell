/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 22:26:28 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/10 12:53:45 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_word(char *line, int i)
{
	char	quote;

	while (line[i] && !is_space(line[i]))
	{
		while (line[i] && !is_space(line[i]) && !is_quote(line[i]))
			i++;
		if (is_quote(line[i]))
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i])
				i++;
		}
	}
	return (i);
}

static char	**ft_add_lines(char **tab, char *line, int i, int row)
{
	int		save_i;

	while (line[i])
	{
		i = skip_spaces(line, i);
		save_i = i;
		i = skip_word(line, i);
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

char	**split_spaces(t_line *line, t_var *lst_var, char *block)
{
	char	**tab;
	int		save_i;
	int		row;
	int		i;

	i = 0;
	row = 0;
	if (!block)
		return (NULL);
	while (block[i])
	{
		i = skip_spaces(block, i);
		save_i = i;
		i = skip_word(block, i);
		if (i > save_i)
			row++;
	}
	tab = (char **)malloc(sizeof(char *) * (row + 1));
	if (!tab)
		error_memory_failed(line, lst_var);
	tab[row] = NULL;
	tab = ft_add_lines(tab, block, 0, 0);
	if (!tab)
		error_memory_failed(line, lst_var);
	return (tab);
}
