/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_newline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:05:24 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 16:55:53 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_word_newline(char *line, int i)
{
	char	quote;

	while (line[i] && line[i] != '\n')
	{
		if (is_quote(line[i]))
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
		}
		if (line[i])
			i++;
	}
	return (i);
}

static char	**ft_add_lines(char **tab, char *line, int i, int row)
{
	int		save_i;

	while (line && line[i])
	{
		while (line[i] && line[i] == '\n')
			i++;
		save_i = i;
		i = parse_word_newline(line, i);
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

char	**split_newline(t_line *line, t_var *lst_var, char *s)
{
	char	**tab;
	int		save_i;
	int		row;
	int		i;

	i = 0;
	row = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == '\n')
			i++;
		save_i = i;
		i = parse_word_newline(s, i);
		if (i > save_i)
			row++;
		if (s[i])
			i++;
	}
	tab = (char **)malloc(sizeof(char *) * (row + 1));
	if (!tab)
		error_memory_failed(line, lst_var);
	tab[row] = NULL;
	tab = ft_add_lines(tab, s, 0, 0);
	return (tab);
}
