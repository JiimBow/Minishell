/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_var_unquote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 14:36:36 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/10 14:37:04 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	change_var_sup_quote(t_line *line, const char *s, char *tab, int *j)
{
	char	quote;
	int		i;

	i = 0;
	quote = s[i++];
	while (s[i] && s[i] != quote)
	{
		if (quote == '"' && s[i] == '$' && s[i + 1]
			&& !is_quote(s[i + 1]))
			i += change_variable(line, s + i, tab, j);
		else
			tab[(*j)++] = s[i++];
	}
	return (i + 1);
}

char	*substr_var_unquote(t_line *line, t_var *lst_var, char *s)
{
	char	*tab;
	int		count;
	int		j;
	int		i;

	if (!line->env || !*line->env || !s)
		return (NULL);
	count = get_size_with_variable(line, s, 0, 0);
	tab = ft_calloc(sizeof(char), count + 1);
	if (!tab)
		error_memory_failed(line, lst_var);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
			i += change_var_sup_quote(line, s + i, tab, &j);
		else if (s[i] == '$' && s[i + 1])
			i += change_variable(line, s + i, tab, &j);
		else
			tab[j++] = s[i++];
	}
	free(s);
	return (tab);
}
