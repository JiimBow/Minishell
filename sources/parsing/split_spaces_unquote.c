/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_spaces_unquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 19:53:25 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/10 19:54:57 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_words(char *line, int i)
{
	while (line[i] && !is_space(line[i]))
		i++;
	return (i);
}

static char	**ft_add_lines(char **tab, char *line, int i, int row)
{
	int		save_i;

	while (line[i])
	{
		i = skip_spaces(line, i);
		save_i = i;
		i = skip_words(line, i);
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

char	**split_spaces_unquote(t_line *line, t_var *lst_var, char *block)
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
		i = skip_words(block, i);
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
