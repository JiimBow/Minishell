/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:52:18 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/11 15:53:11 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
