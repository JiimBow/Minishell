/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:20:54 by jodone            #+#    #+#             */
/*   Updated: 2026/01/14 13:10:12 by mgarnier         ###   ########.fr       */
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

void	write_args(char **args, int i)
{
	while (args[i])
	{
		if (args[i][0] == '\0')
		{
			i++;
			continue ;
		}
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
}

int	ft_echo(char **args)
{
	int	i;

	if (!args[1])
		printf("\n");
	else if (ft_strncmp("-n", args[1], 2) != 0)
	{
		write_args(args, 1);
		printf("\n");
	}
	else
	{
		i = skip_option(args, 1);
		write_args(args, i);
	}
	return (0);
}
