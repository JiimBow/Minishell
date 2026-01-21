/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:51 by jodone            #+#    #+#             */
/*   Updated: 2026/01/21 14:09:14 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_and_exit(t_line *line, int sig_exit)
{
	int	exit_code;

	exit_code = 2;
	if (sig_exit || (line->args && !line->args[1]))
		exit_code = sig_exit;
	free_line_struct(line, 1);
	exit(exit_code);
}

static int	arg_isnum(char *args)
{
	int	i;

	i = 0;
	if (args && (args[0] == '-' || args[0] == '+'))
		i++;
	while (args && args[i])
	{
		if (!ft_isdigit(args[i]))
			return (0);
		i++;
	}
	return (1);
}

int	free_before_exit(t_line *line, t_var *lst_var)
{
	write(2, "exit\n", 5);
	if (line->args && line->args[1] && line->args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	rl_clear_history();
	ft_lstclear_var(&lst_var, free);
	if (line->args && !arg_isnum(line->args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, line->args[1], ft_strlen(line->args[1]));
		write(2, ": numeric argument required\n", 29);
	}
	else if (line->args && !g_sig)
		g_sig = ft_atoi(line->args[1]);
	if (line->line)
		free_and_exit(line, g_sig);
	free_line_struct(line, 1);
	exit(g_sig);
}
