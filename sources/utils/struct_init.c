/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:09:31 by jodone            #+#    #+#             */
/*   Updated: 2026/01/26 14:12:20 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_line	*creation_line(t_var *lst_var)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		error_memory_failed(NULL, lst_var);
	line->env = NULL;
	line->new = NULL;
	line->block = NULL;
	line->sig = 0;
	return (line);
}

t_pipe	pipe_init(void)
{
	t_pipe	child;

	child.fdout = -1;
	child.pipefd[0] = -1;
	child.pipefd[1] = -1;
	child.prev_fd = -1;
	return (child);
}
