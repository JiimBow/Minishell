/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:41:39 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/12 14:56:13 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *args)
{
	const char	*cmd = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int		i;

	i = 0;
	if (!args)
		return (0);
	while (cmd[i])
	{
		if (ft_strnstr(args, cmd[i], 5))
			return (1);
		i++;
	}
	return (0);
}

t_arg	*tokenisation(t_arg *data, char **args)
{
	int	i;

	if (!args || !*args)
		return ;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '<' || args[i][0] == '>' || ft_strncmp(args[i], '|', 2))
		{
			data[i].group = OPERATORS;
		}
		else if (is_built_in(args[i]))
		{
			printf("args[%d]: ici on doit appeler les commandes\n", i);
		}
		i++;
	}
	return (data);
}
