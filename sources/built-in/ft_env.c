/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 15:03:16 by jodone            #+#    #+#             */
/*   Updated: 2026/01/30 13:38:57 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char	**envp, char **args)
{
	int	i;

	i = 0;
	if (args && args[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	while (envp && envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
