/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 14:14:13 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/21 17:20:07 by mgarnier         ###   ########.fr       */
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

char	**reduce_args(t_line *line)
{
	char	**new_args;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (line->args[i])
	{
		if (is_redirection(line->args[i]))
		{
			len += 2;
			i++;
		}
		i++;
	}
	new_args = malloc(sizeof(char) * (i - len + 1));
	if (!new_args)
		return (NULL);
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

void	find_redirection(t_line *line)
{
	t_var	*new;
	int		i;

	i = 0;
	while (line->args[i])
	{
		if (is_redirection(line->args[i]))
		{
			new = ft_lst_new_var(NULL, ft_strdup(line->args[i + 1]));
			ft_lstadd_back_var(line->red, new);
			if (ft_strncmp(line->args[i], "<", 2) == 0)
				new->rank = 1;
			else if (ft_strncmp(line->args[i], "<<", 3) == 0)
				new->rank = 2;
			else if (ft_strncmp(line->args[i], ">", 2) == 0)
				new->rank = 3;
			else if (ft_strncmp(line->args[i], ">>", 3) == 0)
				new->rank = 4;
		}
		i++;
	}
	line->args = reduce_args(line);
}
