/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:46:37 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/29 16:39:49 by jodone           ###   ########.fr       */
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

static void	separate_redirection(t_line *line, t_var *lst_var, int index)
{
	t_var	*new;
	char	*tmp;
	int		i;

	i = 0;
	while (line->args && line->args[i])
	{
		if (is_redirection(line->args[i++]))
		{
			line->quote = is_quote_in_tab(line->args[i]);
			if (ft_strncmp(line->args[i - 1], "<<", 3) != 0)
			{
				tmp = ft_strdup(line->args[i]);
				tmp = substr_var(line, lst_var, tmp, 0);
			}
			else
				tmp = strdup_unquote(line, lst_var, line->args[i], 0);
			new = ft_lst_new_var(NULL, tmp, index);
			free(tmp);
			if (ft_strncmp(line->args[i - 1], "<", 2) == 0)
				new->rank = REDIR_IN;
			else if (ft_strncmp(line->args[i - 1], "<<", 3) == 0)
				new->rank = REDIR_HEREDOC;
			else if (ft_strncmp(line->args[i - 1], ">", 2) == 0)
				new->rank = REDIR_OUT;
			else if (ft_strncmp(line->args[i - 1], ">>", 3) == 0)
				new->rank = REDIR_APPEND;
			ft_lstadd_back_var(&line->redirec, new);
		}
	}
}

int	parse_redirection(t_line *line, t_var *lst_var)
{
	t_var	*tmp;
	int		i;

	i = 0;
	while (line->block && line->block[i])
	{
		line->args = split_spaces(line, lst_var, line->block[i]);
		separate_redirection(line, lst_var, i);
		// line->block[i] = substr_var(line, lst_var, line->block[i], 0);
		free_double_tab(line->args);
		line->args = NULL;
		i++;
	}
	tmp = line->redirec;
	int	index = 0;
	while (index < i && line->sig != 130)
	{
		if (tmp && tmp->index == index)
		{
			if (tmp->rank == 2)
				line->sig = r_here_doc(line, lst_var, tmp);
			tmp = tmp->next;
		}
		if (quotes_unclosed(line->line))
		{
			write(2, "minishell: syntax error unclosed quote\n", 39);
			line->sig = 2;
			return (1);
		}
		int syntax = 0;
		syntax = syntax_error(line->new, 't', 'q', 0);
		if (syntax != 0)
		{
			write(2, "minishell: syntax error near unexpected token \" ", 48);
			write(2, &line->new[syntax], 1);
			write(2, " \"\n", 3);
			free(line->new);
			line->new = NULL;
			line->sig = 2;
			return (1);
		}
		index++;
	}
	return (0);
	// while (tmp && line->sig != 130)
	// {
	// 	if (tmp->rank == 2)
	// 		line->sig = r_here_doc(line, lst_var, tmp);
	// 	tmp = tmp->next;
	// }
}
