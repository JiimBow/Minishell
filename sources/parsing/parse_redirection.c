/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:46:37 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 11:13:22 by jodone           ###   ########.fr       */
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

static t_var	*crea_node_red(t_line *line, t_var *lst_var, int index, int i)
{
	t_var	*new;
	char	*tmp;
	char	*tmp2;

	if (ft_strncmp(line->args[i - 1], "<<", 3) != 0)
	{
		tmp = ft_strdup(line->args[i]);
		tmp = substr_var(line, lst_var, tmp);
	}
	else
		tmp = strdup_unquote(line, lst_var, line->args[i], 0);
	tmp2 = strdup_unquote(line, lst_var, line->args[i], 0);
	new = ft_lst_new_var(tmp2, tmp, index);
	free(tmp2);
	free(tmp);
	return (new);
}

static void	separate_redirection(t_line *line, t_var *lst_var, int index)
{
	t_var	*new;
	int		i;

	i = 0;
	while (line->args && line->args[i])
	{
		if (is_redirection(line->args[i++]))
		{
			line->quote = is_quote_in_tab(line->args[i]);
			new = crea_node_red(line, lst_var, index, i);
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

int	parse_redirection(t_line *line, t_var *lst_var, int pipe_error_block)
{
	t_var	*tmp;
	int		syntax;
	int		index;
	int		i;

	i = 0;
	while (line->block && line->block[i])
	{
		line->args = split_spaces(line, lst_var, line->block[i]);
		separate_redirection(line, lst_var, i);
		free_double_tab(line->args);
		line->args = NULL;
		i++;
	}
	tmp = line->redirec;
	index = 0;
	while (index < i && line->sig != 130 && index <= pipe_error_block)
	{
		if (tmp && tmp->index == index)
		{
			if (tmp->rank == 2)
				line->sig = r_here_doc(line, lst_var, tmp);
			tmp = tmp->next;
		}
		if (quotes_unclosed(line->line))
		{
			ft_putstr_fd("minishell: syntax error unclosed quote\n", 2);
			line->sig = 2;
			return (1);
		}
		syntax = syntax_error(line->block[index], 't', 'q', 0);
		if (syntax != 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
			ft_putstr_fd("`newline'\n", 2);
			// free(line->new);
			// line->new = NULL;
			line->sig = 2;
			return (1);
		}
		index++;
	}
	return (0);
}
