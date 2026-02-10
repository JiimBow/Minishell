/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:51:07 by jodone            #+#    #+#             */
/*   Updated: 2026/02/10 17:48:56 by jodone           ###   ########.fr       */
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

static void	write_parse(char *str)
{
	write(2, "minishell: export: ", 19);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 26);
}

int	parse_export(char *name, char *args)
{
	if (ft_strncmp(args, "=", 2) == 0)
	{
		write_parse("=");
		return (0);
	}
	else if (!name)
	{
		write_parse(args);
		return (0);
	}
	else if ((!ft_isalpha(name[0]) && name[0] != '_')
		|| !check_car(name))
	{
		write_parse(name);
		return (0);
	}
	return (1);
}
