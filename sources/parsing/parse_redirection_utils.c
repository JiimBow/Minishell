/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:52:52 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/29 19:31:13 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	variable_not_existed(t_line *line, t_var *lst_var, char *tab)
{
	char	*tmp;

	tmp = ft_substr(tab, 0, ft_strlen(tab));
	tmp = substr_var(line, lst_var, tmp);
	if (tmp && tmp[0] == '\0')
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

static int	count_size_no_redirection(t_line *line, t_var *lst_var, int *i)
{
	int	count;

	*i = 0;
	count = 0;
	while (line->args[*i])
	{
		if (is_redirection(line->args[*i]))
			count += 2;
		else if (variable_not_existed(line, lst_var, line->args[*i]))
			count++;
		(*i)++;
	}
	return (count);
}

static char	**reduce_args(t_line *line, t_var *lst_var, int i)
{
	char	**new_args;
	int		len;

	if (!line->args)
		return (NULL);
	len = count_size_no_redirection(line, lst_var, &i);
	new_args = (char **)malloc(sizeof(char *) * (i - len + 1));
	if (!new_args)
		error_memory_failed(line, lst_var);
	new_args[i - len] = NULL;
	i = 0;
	len = 0;
	while (line->args[i])
	{
		if (is_redirection(line->args[i]))
			i += 2;
		else if (variable_not_existed(line, lst_var, line->args[i]))
			i++;
		else
			new_args[len++] = ft_strdup(line->args[i++]);
	}
	free_double_tab(line->args);
	return (new_args);
}

void	replace_args_without_redirection(t_line *line, t_var *lst_var)
{
	char	*tmp;
	int		i;

	line->args = reduce_args(line, lst_var, 0);
	i = 0;
	while (line->args && line->args[i])
	{
		tmp = substr_var_unquote(line, lst_var, line->args[i]);
		line->args[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
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
