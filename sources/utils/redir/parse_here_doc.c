/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:23:49 by jodone            #+#    #+#             */
/*   Updated: 2026/01/30 12:30:59 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parse_here_doc(t_line *line, t_var *lst_var, t_var *tmp, int index)
{
	int	syntax;

	while (tmp && tmp->index == index)
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
		line->sig = 2;
		return (1);
	}
	return (0);
}
