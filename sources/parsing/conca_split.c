/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conca_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 20:54:52 by jodone            #+#    #+#             */
/*   Updated: 2026/01/29 21:39:23 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_words_quotes(char *arg)
{
	int	count;
	int	i;
	int	save_i;

	count = 0;
	i = 0;
	while (arg[i])
	{
		i = skip_spaces(arg, i);
		save_i = i;
		i = parse_word(arg, i);
		if (i > save_i)
			count++;
	}
	return (count);
}

int	ft_count_args(char **args)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (args && args[i])
		count += count_words_quotes(args[i++]);
	return (count);
}

char	**conca_split(t_line *line)
{
	(void)line;
	return (NULL);
}
