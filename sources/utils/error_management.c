/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:44:00 by jodone            #+#    #+#             */
/*   Updated: 2026/01/29 19:09:34 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	write_error(char *cmd_name, int code)
{
	if (code == 1)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	if (code == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	if (code == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	if (code == 4)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
}
