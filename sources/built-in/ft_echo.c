/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:20:54 by jodone            #+#    #+#             */
/*   Updated: 2026/01/14 12:07:07 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	skip_option(char **args, int i)
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

void	write_args(char **args, int i, int sig)
{
	while (args[i])
	{
		if (args[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (ft_strncmp(args[i], "$?", 3) == 0)	
		{
			printf("%i", sig);
			i++;
			continue ;
		}
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
}

int	ft_echo(char **args, int sig)
{
	int	i;

	if (!args[1])
		printf("\n");
	else if (ft_strncmp("-n", args[1], 2) != 0)
	{
		write_args(args, 1, sig);
		printf("\n");
	}
	else
	{
		i = skip_option(args, 1);
		write_args(args, i, sig);
	}
	return (0);
}
