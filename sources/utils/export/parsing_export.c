/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:51:07 by jodone            #+#    #+#             */
/*   Updated: 2026/01/16 23:29:27 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_car(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	parse_export(char *args)
{
	if ((!ft_isalpha(args[0]) && args[0] != '_')
		|| !check_car(args))
	{
		write(2, "minishell: export: ", 19);
		write(2, args, ft_strlen(args));
		write(2, ": not a valid identifier\n", 26);
		return (0);
	}
	return (1);
}
