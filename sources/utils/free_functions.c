/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:00:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/26 14:08:19 by mgarnier         ###   ########.fr       */
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
	free_double_tab(line->env);
	free_double_tab(line->args);
	free_double_tab(line->block);
	if (line->line)
		free(line->line);
	line->line = NULL;
	if (line->new)
		free(line->new);
	line->new = NULL;
	ft_lstclear_var(&line->red, free);
	if (all == 1)
		free(line);
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
