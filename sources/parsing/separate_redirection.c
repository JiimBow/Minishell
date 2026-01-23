/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:52:36 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/23 16:01:00 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(char *args)
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

static char	**reduce_args(t_line *line, int i)
{
	char	**new_args;
	int		len;

	len = 0;
	if (!line->args)
		return (NULL);
	while (line->args[i])
		if (is_redirection(line->args[i++]))
			len += 2;
	new_args = (char **)malloc(sizeof(char *) * (i - len + 1));
	if (!new_args)
		return (NULL);
	new_args[i - len] = NULL;
	i = 0;
	len = 0;
	while (line->args[i])
	{
		if (is_redirection(line->args[i]))
			i += 2;
		else
			new_args[len++] = ft_strdup(line->args[i++]);
	}
	free_double_tab(line->args);
	return (new_args);
}

static void	replace_args_without_redirection(t_line *line)
{
	char	*tmp;
	int		i;

	line->args = reduce_args(line, 0);
	i = 0;
	while (line->args[i])
	{
		tmp = strdup_unquote(line->args[i], 0, 0);
		free(line->args[i]);
		line->args[i] = ft_strdup(tmp);
		free(tmp);
		i++;
	}
}

static int	is_quote_in_tab(char *tab)
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

void	separate_redirection(t_line *line)
{
	t_var	*new;
	char	*tmp;
	int		i;

	i = 0;
	while (line->args && line->args[i])
	{
		if (is_redirection(line->args[i]))
		{
			line->quote = is_quote_in_tab(line->args[i + 1]);
			tmp = strdup_unquote(line->args[i + 1], 0, 0);
			new = ft_lst_new_var(NULL, tmp);
			free(tmp);
			if (ft_strncmp(line->args[i], "<", 2) == 0)
				new->rank = REDIR_IN;
			else if (ft_strncmp(line->args[i], "<<", 3) == 0)
				new->rank = REDIR_HEREDOC;
			else if (ft_strncmp(line->args[i], ">", 2) == 0)
				new->rank = REDIR_OUT;
			else if (ft_strncmp(line->args[i], ">>", 3) == 0)
				new->rank = REDIR_APPEND;
			ft_lstadd_back_var(&line->red, new);
		}
		i++;
	}
	replace_args_without_redirection(line);
}
