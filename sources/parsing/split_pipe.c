/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:16:08 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 11:35:17 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_word_pipe(char *line, int i)
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

static char	**ft_add_lines(char **tab, char *line, int i, int row)
{
	int		save_i;

	while (line[i])
	{
		i = skip_spaces(line, i);
		save_i = i;
		i = parse_word_pipe(line, i);
		if (i > save_i || line[i] == '|')
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

void	split_pipe(t_line *line, t_var *lst_var)
{
	int		save_i;
	int		i;

	i = 0;
	line->row = 0;
	if (!line->new)
		return ;
	while (line->new[i])
	{
		i = skip_spaces(line->new, i);
		save_i = i;
		i = parse_word_pipe(line->new, i);
		if (i > save_i || line->new[i] == '|')
			line->row++;
		if (line->new[i])
			i++;
	}
	line->block = (char **)malloc(sizeof(char *) * (line->row + 1));
	if (!line->block)
		error_memory_failed(line, lst_var);
	line->block[line->row] = NULL;
	line->block = ft_add_lines(line->block, line->new, 0, 0);
}
