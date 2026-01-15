/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:19:28 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/15 11:04:30 by mgarnier         ###   ########.fr       */
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

static char	**ft_add_lines(t_env *env, t_line *line, int n)
{
	char	**tab;
	char	quote;
	int		start;
	int		i;

	tab = (char **)malloc(sizeof(char *) * (n + 1));
	if (!tab)
		return (NULL);
	tab[n] = NULL;
	i = 0;
	n = 0;
	while (line->line[i])
	{
		while (line->line[i] && is_spaces(line->line[i]))
			i++;
		start = i;
		while (line->line[i] && !is_spaces(line->line[i]))
		{
			while (line->line[i] && !is_spaces(line->line[i]) && !is_quote(line->line[i]))
				i++;
			if (is_quote(line->line[i]))
			{
				quote = line->line[i++];
				while (line->line[i++] != quote)
					;
			}
		}
		if (i > start)
		{
			tab[n] = ft_substr_variable(env->env, line->line + start, 0, i - start);
			if (!tab[n])
			{
				ft_free_tab(tab, n);
				return (NULL);
			}
			n++;
		}
	}
	return (tab);
}

char	**ft_split_line(t_env *env, t_line *line)
{
	char	**tab;
	char	quote;
	int		check;
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (line->line[i])
	{
		check = 0;
		while (line->line[i] && is_spaces(line->line[i]))
			i++;
		while (line->line[i] && !is_spaces(line->line[i]))
		{
			while (line->line[i] && !is_spaces(line->line[i]) && !is_quote(line->line[i]))
			{
				check = 1;
				i++;
			}
			if (is_quote(line->line[i]))
			{
				check = 1;
				quote = line->line[i++];
				while (line->line[i] && line->line[i] != quote)
					i++;
				if (line->line[i] && line->line[i] == quote)
					i++;
				else
				{
					write(2, "minishell: syntax error\n", 24);
					g_sig = 2;
					return (NULL);
				}
			}
		}
		if (check == 1)
			n++;
	}
	tab = ft_add_lines(env, line, n);
	if (!tab)
		return (NULL);
	return (tab);
}
