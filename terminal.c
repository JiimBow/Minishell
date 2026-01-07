/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:52:55 by jodone            #+#    #+#             */
/*   Updated: 2026/01/07 15:45:29 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		printf("");
		rl_redisplay();
	}
}

int	main(void)
{
	char	*line;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	while (1)
	{
		line = readline("minishell> ");
		if (line && *line)
		{
			add_history(line);
			free(line);
		}
		else if(!line)
			break ;
	}
	return (0);
}
