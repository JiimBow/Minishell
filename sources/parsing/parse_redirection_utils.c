/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:52:52 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/10 16:39:17 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *args)
{
	if (ft_strncmp(args, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(args, "<<", 3) == 0)
		return (1);
	else if (ft_strncmp(args, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(args, ">>", 3) == 0)
		return (1);
	return (0);
}

int	is_quote_in_tab(char *tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
	{
		if (is_quote(tab[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*strdup_unquote(t_line *line, t_var *lst_var, char *s, int j)
{
	char	*new;
	char	quote;
	int		n;
	int		i;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	new = ft_calloc(sizeof(char), n + 1);
	if (!new)
		error_memory_failed(line, lst_var);
	i = 0;
	while (i < n)
	{
		if (is_quote(s[i]) && s[i + 1])
		{
			quote = s[i++];
			while (i < n && s[i] != quote)
				new[j++] = s[i++];
			i++;
		}
		else
			new[j++] = s[i++];
	}
	return (new);
}
