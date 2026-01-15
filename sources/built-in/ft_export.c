/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 10:10:11 by jodone            #+#    #+#             */
/*   Updated: 2026/01/15 10:20:57 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	rank_var(t_var **lst_var)
{
	t_var	*tmp;
	int		rank;
	int		lst_size;

	lst_size = ft_lstsize_var(lst_var);
	rank = 0;
	while (rank < lst_size)
	{
		tmp = *lst_var;
		
	}
}
