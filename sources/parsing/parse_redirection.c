/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:46:37 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 16:46:59 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (parse_here_doc(line, lst_var, tmp, index) == 1)
			return (1);
		index++;
	}
	return (0);
}
