/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_line_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:00:09 by jodone            #+#    #+#             */
/*   Updated: 2026/01/19 15:29:52 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_line_struct(t_line *line)
{
	free_double_tab(line->args);
	free_double_tab(line->env);
	free(line->line);
	free(line->new);
	free(line);
}
