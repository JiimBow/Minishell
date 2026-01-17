/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranking_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:33:43 by jodone            #+#    #+#             */
/*   Updated: 2026/01/16 23:29:32 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	already_sorted(t_var **lst_var)
{
	t_var	*tmp;

	tmp = *lst_var;
	while (tmp)
	{
		if (tmp->rank == -1)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

static void	reset_rank(t_var **lst_var)
{
	t_var	*tmp;

	tmp = *lst_var;
	while (tmp)
	{
		tmp->rank = -1;
		tmp = tmp->next;
	}
}

static char	*get_first_name(t_var **lst_var)
{
	t_var	*tmp;
	char	*low;

	tmp = *lst_var;
	while (tmp)
	{
		if (tmp->rank == -1)
		{
			low = ft_strdup(tmp->name);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = *lst_var;
	while (tmp)
	{
		if (tmp->rank == -1 && ft_strncmp(low, tmp->name, ft_strlen(low)) > 0)
		{
			free(low);
			low = ft_strdup(tmp->name);
		}
		tmp = tmp->next;
	}
	return (low);
}

void	rank_var(t_var **lst_var)
{
	t_var	*tmp;
	int		rank;
	int		lst_size;
	char	*low_name;

	lst_size = ft_lstsize_var(*lst_var);
	reset_rank(lst_var);
	rank = 0;
	while (rank < lst_size)
	{
		tmp = *lst_var;
		low_name = get_first_name(lst_var);
		while (tmp)
		{
			if (ft_strncmp(low_name, tmp->name, ft_strlen(low_name)) == 0)
			{
				tmp->rank = rank;
				rank++;
				break ;
			}
			tmp = tmp->next;
		}
		free(low_name);
	}
}
