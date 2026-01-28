/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:08:01 by jodone            #+#    #+#             */
/*   Updated: 2026/01/28 15:56:58 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sign_here_d(int signal)
{
	g_sig = signal;
	if (signal == SIGINT)
	{
		ft_printf("\n");
		close(0);
	}
}

void	global_handle(t_line *line, long g_sig)
{
	if (WIFSIGNALED(g_sig))
		line->sig = WTERMSIG(g_sig) + 128;
	g_sig = 0;
}

void	handle_sigint(int signal)
{
	g_sig = signal;
	if (g_sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf("\n");
		rl_redisplay();
	}
}

void	get_last_status(__pid_t pid, __pid_t last_pid, t_line *line)
{
	int	last_status;
	int	status;

	while (pid > 0)
	{
		if (pid == last_pid)
			last_status = status;
		pid = wait(&status);
	}
	line->sig = return_value(last_status);
}
