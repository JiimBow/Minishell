/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:00:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/21 21:26:14 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_line_struct(t_line *line, int all)
{
	free_double_tab(line->args);
	free_double_tab(line->env);
	free(line->line);
	line->line = NULL;
	free(line->new);
	line->new = NULL;
	free_double_tab(line->block);
	ft_lstclear_var(&line->red, free);
	if (all == 1)
		free(line);
}

void	free_all(t_line *line, t_var *lst_var)
{
	ft_lstclear_var(&lst_var, free);
	free_line_struct(line, 1);
}
