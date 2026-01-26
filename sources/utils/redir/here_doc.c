/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:04:05 by jodone            #+#    #+#             */
/*   Updated: 2026/01/26 16:41:08 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	here_doc_proc(t_line *line, char *until_lim, char *content, int pipe_doc)
{
	write(0, "> ", 2);
	until_lim = get_next_line(STDIN_FILENO);
	if (!until_lim)
		return (1);
	if (ft_strncmp(until_lim, content, ft_strlen(content)) == 0
		&& (until_lim[ft_strlen(content)] == '\n'
			|| until_lim[ft_strlen(content)] == '\0'))
	{
		free(until_lim);
		return (1);
	}
	if (line->quote == 0)
		until_lim = substr_var(line, until_lim);
	write(pipe_doc, until_lim, ft_strlen(until_lim));
	free(until_lim);
	return (0);
}
