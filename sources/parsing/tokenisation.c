/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:41:39 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/12 15:59:04 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_dir(char *s)
{
	struct stat	st;

	if (stat(s, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			return (1);
		}
	}
	return (0);
}

static int	is_built_in(char *args)
{
	const char	*cmd[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			i;

	i = 0;
	if (!args)
		return (0);
	while (cmd[i])
	{
		if (ft_strncmp(args, cmd[i], ft_strlen(cmd[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

t_arg	*tokenisation(t_arg *data, char **args, int i)
{
	if (!args || !*args)
		return (NULL);
	while (args[i])
		i++;
	data = (t_arg *)malloc(sizeof(t_arg) * (i + 1));
	if (!data)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (args[i][0] == '<' || args[i][0] == '>' || ft_strncmp(args[i], "|", 2))
			data[i].group = OPERATORS;
		else if (args[i][0] == '-')
			data[i].group = OPTIONS;
		else if (is_built_in(args[i]))
			data[i].group = BUILT_IN;
		else if (is_dir(args[i]))
			data[i].group = DIRECTORIES;
		else
			data[i].group = FILES;
		i++;
	}
	return (data);
}
