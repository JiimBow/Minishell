/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:37:21 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/09 11:03:54 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_file_or_dir(t_arg *data, char *s, int i)
{
	struct stat	st;

	if (stat(s, &st) == 0)
	{
		if (S_ISREG(st.st_mode))
		{
			data[i].group = FILES;
			printf("arg: %d, groupe: %d\n", data[i].index, data[i].group);
		}
		else if (S_ISDIR(st.st_mode))
		{
			data[i].group = DIRECTORIES;
			printf("arg: %d, groupe: %d\n", data[i].index, data[i].group);
		}
		else
			return (0); // existe mais autre type
	}
	else
		return (-1); // n'existe pas
	return (1);
}

char	**parse_line(t_arg *data, char *line)
{
	char	**args;
	int		count;
	int		i;

	args = ft_split_line(line, ' ', 0, 0);
	if (!args || !*args)
		return (NULL);
	count = 0;
	while (args[count])
		count++;
	data = (t_arg *)malloc(sizeof(t_arg) * (count + 1));
	if (!data)
	{
		free_double_tab(args);
		return (NULL);
	}
	i = 0;
	while (args[i])
	{
		data[i].index = i;
		is_file_or_dir(data, args[i], i); // int retour pour erreurs?
		i++;
	}
	return (args);
}
