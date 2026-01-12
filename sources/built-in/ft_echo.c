/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:20:54 by jodone            #+#    #+#             */
/*   Updated: 2026/01/12 16:14:37 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_option(char **args, int i)
{
	while (ft_strncmp("-n", args[i], 3) == 0)
		i++;
	return (i);
}

void	write_args(char **args, int i)
{
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
}

void	ft_echo(char **args)
{
	int	i;

	if (!args[1])
		printf("\n");
	else if (ft_strncmp("-n", args[1], 3) != 0)
	{
		write_args(args, 1);
		printf("\n");
	}
	else
	{
		i = skip_option(args, 2);
		write_args(args, i);
	}
}
