/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:20:54 by jodone            #+#    #+#             */
/*   Updated: 2026/01/21 18:48:26 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_option(char **args, int i)
{
	int	j;
	int	is_option;

	while (ft_strncmp("-n", args[i], 2) == 0)
	{
		is_option = 0;
		j = 1;
		while (args[i][j])
		{
			if (args[i][j] != 'n')
			{
				is_option = 1;
				break ;
			}
			j++;
		}
		if (is_option == 1)
			break ;
		i++;
	}
	return (i);
}

static void	write_args(char **args, int i)
{
	while (args[i])
	{
		ft_printf("%s", args[i++]);
		if (args[i])
			ft_printf(" ");
	}
}

int	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		ft_printf("\n");
		return (0);
	}
	else if (ft_strncmp("-n", args[1], 2) == 0)
		i = skip_option(args, 1);
	if (i == 1)
	{
		write_args(args, 1);
		ft_printf("\n");
	}
	else
		write_args(args, i);
	return (0);
}
