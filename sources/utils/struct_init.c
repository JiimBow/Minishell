/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:09:31 by jodone            #+#    #+#             */
/*   Updated: 2026/01/22 16:27:47 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_line	*creation_line(void)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->env = NULL;
	line->new = NULL;
	line->block = NULL;
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
