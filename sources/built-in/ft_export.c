/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:10:11 by jodone            #+#    #+#             */
/*   Updated: 2026/01/15 15:34:54 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	manage_display(char *name, char *content)
{
	if (content)
		printf("declare -x %s=\"%s\"\n", name, content);
	else
		printf("declare -x %s\n", name);
}

static void	display_export(t_var **lst_var)
{
	t_var	*tmp;
	int		lst_size;
	int		count;

	lst_size = ft_lstsize_var(*lst_var);
	count = 0;
	while (count < lst_size)
	{
		tmp = *lst_var;
		while (tmp)
		{
			if (tmp->rank == count)
			{
				manage_display(tmp->name, tmp->content);
				break ;
			}
			tmp = tmp->next;
		}
		count++;
	}
}

int	ft_export(t_var **lst_var, char **args)
{
	if (!args[1])
	{
		if (!already_sorted(lst_var))
		{
			reset_rank(lst_var);
			rank_var(lst_var);
		}
		display_export(lst_var);
	}
	return (0);
}
