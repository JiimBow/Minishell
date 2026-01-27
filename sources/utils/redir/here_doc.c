/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:04:05 by jodone            #+#    #+#             */
/*   Updated: 2026/01/27 13:26:03 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	hd_proc(t_line *line, t_var *lst_var, char *content, int pipe_doc)
{
	char	*until_lim;

	until_lim = NULL;
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
		until_lim = substr_var(line, lst_var, until_lim);
	write(pipe_doc, until_lim, ft_strlen(until_lim));
	free(until_lim);
	return (0);
}
