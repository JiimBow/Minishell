/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:49:00 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/07 13:56:02 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (line && *line)
			add_history(line);
		free(line);
	}
	return (0);
}