/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:04:05 by jodone            #+#    #+#             */
/*   Updated: 2026/01/27 17:07:58 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	hd_proc(t_line *line, t_var *lst_var, char *content, int pipe_doc)
{
	char	*until_lim;
	int		empty_line;

	empty_line = 0;
	until_lim = NULL;
	while (1)
	{
		until_lim = readline("> ");
		if (g_sig == SIGINT)
			return (1);
		if (until_lim)
			break ;
		if(!until_lim && empty_line == 0)
		{
			ft_putstr_fd("minishell: warning: here-document at line ", 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(content, 2);
			ft_putstr_fd("')\n", 2);
			return (1);
		}
		free(until_lim);
		empty_line = 1;
	}	
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
	write(pipe_doc, "\n", 1);
	free(until_lim);
	return (0);
}
