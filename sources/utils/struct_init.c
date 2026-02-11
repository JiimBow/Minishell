/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:09:31 by jodone            #+#    #+#             */
/*   Updated: 2026/02/11 11:14:28 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_line	*creation_line(t_var *lst_var)
{
	t_line	*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		error_memory_failed(NULL, lst_var);
	line->home = get_env_path(lst_var, "HOME");
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
