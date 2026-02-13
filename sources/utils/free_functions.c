/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:00:09 by jodone            #+#    #+#             */
/*   Updated: 2026/02/13 10:58:59 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_double_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	return (NULL);
}

void	free_line_struct(t_line *line, int all)
{
	line->env = free_double_tab(line->env);
	line->args = free_double_tab(line->args);
	line->block = free_double_tab(line->block);
	if (line->line)
	{
		free(line->line);
		line->line = NULL;
	}
	if (line->new_ln)
	{
		free(line->new_ln);
		line->new_ln = NULL;
	}
	ft_lstclear_var(&line->redirec, free);
	if (all == 1)
	{
		line->ex_block = free_double_tab(line->ex_block);
		free(line->home);
		free(line);
	}
}

void	free_all(t_line *line, t_var *lst_var)
{
	if (lst_var)
		ft_lstclear_var(&lst_var, free);
	if (line)
		free_line_struct(line, 1);
}

void	error_memory_failed(t_line *line, t_var *lst_var)
{
	if (line || lst_var)
		free_all(line, lst_var);
	write(2, "Error: memory allocation failed\n", 32);
	exit(EXIT_FAILURE);
}
