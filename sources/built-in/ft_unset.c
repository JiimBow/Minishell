/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 17:06:53 by jodone            #+#    #+#             */
/*   Updated: 2026/02/11 16:06:09 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_first_node(t_var **lst_var)
{
	t_var	*supp;

	if (!lst_var || !*lst_var)
		return ;
	supp = *lst_var;
	*lst_var = supp->next;
	free(supp->content);
	free(supp->name);
	free(supp);
}

static void	remove_node(t_var *current_lst)
{
	t_var	*supp;

	supp = current_lst->next;
	current_lst->next = supp->next;
	free(supp->name);
	free(supp->content);
	free(supp);
}

static void	remove_var(t_var **lst_var, char *name)
{
	t_var	*tmp;
	int		len_name;

	tmp = *lst_var;
	len_name = ft_strlen(name);
	if (ft_strncmp(name, tmp->name, len_name + 1) == 0)
	{
		remove_first_node(lst_var);
		rank_var(lst_var);
		return ;
	}
	while (tmp)
	{
		if (tmp->next)
		{
			if (ft_strncmp(name, tmp->next->name, len_name + 1) == 0)
			{
				remove_node(tmp);
				rank_var(lst_var);
				break ;
			}
		}
		tmp = tmp->next;
	}
}

int	ft_unset(t_line *line, t_var **lst_var)
{
	int	i;

	i = 1;
	while (line->args[i])
	{
		remove_var(lst_var, line->args[i]);
		i++;
	}
	return (0);
}
