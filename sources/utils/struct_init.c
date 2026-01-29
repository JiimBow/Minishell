/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:09:31 by jodone            #+#    #+#             */
/*   Updated: 2026/01/29 19:58:47 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	line->prev_sig = 0;
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

void	reinitialization(t_line *line, t_var *lst_var, t_pipe *child)
{
	line->env = ft_copy_env(&lst_var);
	if (!line->env)
		error_memory_failed(line, lst_var);
	line->args = NULL;
	line->block = NULL;
	line->ex_block = NULL;
	line->redirec = NULL;
	line->sig = 0;
	*child = pipe_init();
	line->line = readline("minishell> ");
	if (g_sig == SIGINT)
		global_handle(line);
}
