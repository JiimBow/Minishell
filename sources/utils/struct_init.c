/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:09:31 by jodone            #+#    #+#             */
/*   Updated: 2026/01/20 11:45:55 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_line	*creation_line(void)
{
	t_line	*env;

	env = malloc(sizeof(t_line));
	if (!env)
		return (NULL);
	env->env = NULL;
	env->new = NULL;
	env->block = NULL;
	return (env);
}

t_pipe	pipe_init(int i)
{
	t_pipe	child;

	child.fdin = -1;
	child.fdout = -1;
	child.pipefd[0] = -1;
	child.pipefd[1] = -1;
	child.prev_fd = -1;
	child.index = i;
	return (child);
}
