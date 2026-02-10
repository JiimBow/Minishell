/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:46:45 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/10 10:48:56 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_variables(t_line *line, t_var *lst_var)
{
	char	**copy;
	char	**tab;
	char	**var;
	int		i;
	int		j;
	int		x;
	int		y;

	j = 0;
	while (line->args[j])
		j++;
	copy = (char **)malloc(sizeof(char *) * (j + 1));
	if (!copy)
		error_memory_failed(line, lst_var);
	j = 0;
	while (line->args[j])
	{
		copy[j] = ft_strdup(line->args[j]);
		free(line->args[j]);
		line->args[j] = NULL;
		j++;
	}
	copy[j] = NULL;
	j = 0;
	i = 0;
	while (copy[j])
	{
		tab = split_words(line, lst_var, copy[j]);
		x = 0;
		while (tab[x])
		{
			if (is_quote(tab[x][0]))
			{
				tab[x] = substr_var_unquote(line, lst_var, tab[x]);
				line->args[i] = gnl_strjoin(line->args[i], tab[x]);
			}
			else
			{
				if (tab[x][0] == '$' && tab[x][1] == '\0' && tab[x + 1] != NULL)
				{
					x++;
					continue ;
				}
				tab[x] = substr_var_unquote(line, lst_var, tab[x]);
				if (ft_strchr(tab[x], '=') > ft_strchr(tab[x], ' '))
					var = split_spaces(line, lst_var, tab[x]);
				else
					var = ft_split(tab[x], '\0');
				y = 0;
				while (var && var[y])
				{
					if (y == 0 || ft_strchr(var[0], '='))
						line->args[i] = gnl_strjoin(line->args[i], var[y]);
					else
						line->args[++i] = ft_strdup(var[y]);
					y++;
				}
				free_double_tab(var);
			}
			x++;
		}
		free_double_tab(tab);
		j++;
		i++;
	}
	line->args[i] = NULL;
	free_double_tab(copy);
}
