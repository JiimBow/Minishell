/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:37:21 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/08 16:56:16 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**parse_line(char *line)
{
	char	**args;

	if (!line)
		return (NULL);
	args = ft_split_line(line, ' ', 0, 0);
	if (!args || !*args)
		return (NULL);
	return (args);
}
