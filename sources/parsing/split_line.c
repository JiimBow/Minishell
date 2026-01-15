/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:19:28 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/15 14:58:57 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse_word(char *line, int i)
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
			if (line[i] && line[i] == quote)
				i++;
			else
			{
				write(2, "minishell: syntax error\n", 24);
				g_sig = 2;
				return (-1);
			}
		}
	}
	return (i);
}

static char	**ft_add_lines(t_env *env, t_line *line, int row)
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
	while (line->line[i])
	{
		while (line->line[i] && is_spaces(line->line[i]))
			i++;
		save_i = i;
		i = parse_word(line->line, i);
		if (i > save_i)
		{
			tab[row] = substr_var(env->env, line->line + save_i, i - save_i);
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

char	**split_line(t_env *env, t_line *line)
{
	char	**tab;
	int		save_i;
	int		row;
	int		i;

	i = 0;
	row = 0;
	while (line->line[i])
	{
		while (line->line[i] && is_spaces(line->line[i]))
			i++;
		save_i = i;
		i = parse_word(line->line, i);
		if (i < 0)
			return (NULL);
		if (i > save_i)
			row++;
	}
	tab = ft_add_lines(env, line, row);
	if (!tab)
		return (NULL);
	return (tab);
}
