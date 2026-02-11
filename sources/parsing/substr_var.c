/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:36:00 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/11 15:36:00 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_tab(char **env, const char *s, char *tab, int *j)
{
	char	*name;
	char	*content;
	int		n;

	if (!tab)
		return (0);
	name = get_name(s);
	if (!name)
		return (0);
	content = get_content(env, name);
	n = 0;
	while (content && content[n])
		tab[(*j)++] = content[n++];
	n = ft_strlen(name);
	free(name);
	free(content);
	return (n);
}

int	change_variable(t_line *line, const char *s, char *tab, int *j)
{
	char	*tmp;
	int		count;
	int		i;

	i = 0;
	if (s[i + 1] == '?')
	{
		tmp = ft_itoa(line->prev_sig);
		if (!tmp)
			return (0);
		count = 0;
		while (tmp[count])
			tab[(*j)++] = tmp[count++];
		i += 2;
		free(tmp);
	}
	else if ((s[i + 1] == '_' || ft_isalpha(s[i + 1])))
		i += fill_tab(line->env, s + i + 1, tab, j) + 1;
	else if (is_quote(s[i + 1]))
		i++;
	else
		tab[(*j)++] = s[i++];
	return (i);
}

static int	change_var_in_quote(t_line *line, const char *s, char *tab, int *j)
{
	char	quote;
	int		i;

	i = 0;
	quote = s[i];
	tab[(*j)++] = s[i++];
	while (s[i] != quote)
	{
		if (quote == '"' && s[i] == '$' && s[i + 1]
			&& !is_quote(s[i + 1]))
			i += change_variable(line, s + i, tab, j);
		else
			tab[(*j)++] = s[i++];
	}
	tab[(*j)++] = s[i++];
	return (i);
}

char	*substr_var(t_line *line, t_var *lst_var, char *s)
{
	char	*tab;
	int		count;
	int		j;
	int		i;

	if (!s)
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
			i += change_var_in_quote(line, s + i, tab, &j);
		else if (s[i] == '$')
			i += change_variable(line, s + i, tab, &j);
		else
			tab[j++] = s[i++];
	}
	free(s);
	return (tab);
}
