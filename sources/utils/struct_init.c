/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:09:31 by jodone            #+#    #+#             */
/*   Updated: 2026/01/26 17:08:07 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <time.h>

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

void	reinitialization(t_line *line, t_var *lst_var, t_pipe *child)
{
	line->env = ft_copy_env(&lst_var);
	if (!line->env)
		error_memory_failed(NULL, lst_var);
	line->args = NULL;
	line->block = NULL;
	line->red = NULL;
	*child = pipe_init();
	line->line = readline("minishell> ");
}
