/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:51 by jodone            #+#    #+#             */
/*   Updated: 2026/02/12 13:05:05 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_exit(t_line *line, int code)
{
	write(2, "minishell: exit: ", 17);
	write(2, line->args[1], ft_strlen(line->args[1]));
	write(2, ": numeric argument required\n", 29);
	if (code == 1)
		line->prev_sig = 2;
}

static void	free_and_exit(t_line *line)
{
	int	exit_code;

	exit_code = 2;
	if (line->prev_sig != 0 || (line->args && !line->args[1]))
		exit_code = line->prev_sig;
	free_line_struct(line, 1);
	exit(exit_code);
}

static int	arg_isvalid(char *args)
{
	int	i;

	i = 0;
	if (args && (args[0] == '-' || args[0] == '+'))
		i++;
	if (!args)
		return (1);
	if (!args[i])
		return (0);
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
	int	overflow;

	overflow = 0;
	if (!line->line || (line->block && !line->block[1]))
		write(2, "exit\n", 5);
	if (line->args && !arg_isvalid(line->args[1]))
		write_exit(line, 0);
	else if (line->args && line->args[1] && line->args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	if (line->line && line->args && line->args[1])
	{
		line->prev_sig = ft_atoll(line->args[1], &overflow);
		if (overflow == -1)
			write_exit(line, 1);
	}
	rl_clear_history();
	ft_lstclear_var(&lst_var, free);
	if (line->line)
		free_and_exit(line);
	overflow = line->prev_sig;
	free_line_struct(line, 1);
	exit(overflow);
}
