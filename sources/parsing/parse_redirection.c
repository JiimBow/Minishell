/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:46:37 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/28 13:46:38 by mgarnier         ###   ########.fr       */
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

static char	**reduce_args(t_line *line, t_var *lst_var, int i)
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
		error_memory_failed(line, lst_var);
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

void	replace_args_without_redirection(t_line *line, t_var *lst_var)
{
	char	*tmp;
	int		i;

	line->args = reduce_args(line, lst_var, 0);
	i = 0;
	while (line->args && line->args[i])
	{
		tmp = strdup_unquote(line, lst_var, line->args[i], 0);
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

void	parse_redirection(t_line *line, t_var *lst_var)
{
	int	i;

	i = 0;
	while (line->block && line->block[i])
	{
		line->block[i] = substr_var(line, lst_var, line->block[i]);
		line->args = split_spaces(line, lst_var, line->block[i]);
		separate_redirection(line, lst_var, i);
		free_double_tab(line->args);
		line->args = NULL;
		i++;
	}
	t_var *tmp = line->redirec;
	while (tmp)
	{
		if (tmp->rank == 2)
			r_here_doc(line, lst_var, tmp);
		tmp = tmp->next;
	}
}
