/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:46:45 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/10 11:31:59 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_copy(t_line *line, t_var *lst_var)
{
	char	**copy;
	int	i;

	i = 0;
	while (line->args[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		error_memory_failed(line, lst_var);
	i = 0;
	while (line->args[i])
	{
		copy[i] = ft_strdup(line->args[i]);
		free(line->args[i]);
		line->args[i] = NULL;
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	replace_variables(t_line *line, t_var *lst_var)
{
	char	**copy;
	char	**word;
	char	**var;
	int		i;
	int		j;
	int		x;
	int		y;

	copy = create_copy(line, lst_var);
	j = 0;
	i = 0;
	while (copy[j])
	{
		word = split_words(line, lst_var, copy[j]);
		x = 0;
		while (word[x])
		{
			if (is_quote(word[x][0]))
			{
				word[x] = substr_var_unquote(line, lst_var, word[x]);
				line->args[i] = gnl_strjoin(line->args[i], word[x]);
			}
			else
			{
				if (ft_strnstr(word[x], "$", 2) && word[x + 1] != NULL)
				{
					x++;
					continue ;
				}
				word[x] = substr_var_unquote(line, lst_var, word[x]);
				if (ft_strchr(word[x], '=') > ft_strchr(word[x], ' '))
					var = split_spaces(line, lst_var, word[x]);
				else
					var = ft_split(word[x], '\0');
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
		free_double_tab(word);
		j++;
		i++;
	}
	line->args[i] = NULL;
	free_double_tab(copy);
}
