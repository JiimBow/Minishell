/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:08:01 by jodone            #+#    #+#             */
/*   Updated: 2026/02/11 16:03:47 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig_cmd(int signal)
{
	g_sig = signal;
	if (g_sig == SIGINT)
		ft_putstr_fd("\n", 2);
}

void	handle_sign_here_d(int signal)
{
	g_sig = signal;
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		close(0);
	}
}

void	global_handle(t_line *line)
{
	if (WIFSIGNALED(g_sig))
		line->prev_sig = WTERMSIG(g_sig) + 128;
	g_sig = 0;
}

void	handle_sigint(int signal)
{
	g_sig = signal;
	if (g_sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 2);
		rl_redisplay();
	}
}

void	handle_sig_quit(int signal)
{
	g_sig = signal;
	if (g_sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 2);
	}
}
