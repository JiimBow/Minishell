/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:59:25 by jodone            #+#    #+#             */
/*   Updated: 2026/01/15 17:00:24 by jodone           ###   ########.fr       */
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

void	display_export(t_var **lst_var)
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
