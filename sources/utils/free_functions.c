/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:00:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/20 10:29:15 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_struct(t_arg *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (data[i].group != END)
	{
		if (data[i].content)
			free(data[i].content);
		data[i].content = NULL;
		i++;
	}
	free(data);
	data = NULL;
}

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
	if (all == 1)
		free(line);
}
