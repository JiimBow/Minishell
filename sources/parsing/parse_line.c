/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:24:04 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/20 12:24:00 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_unclosed(char *line)
{
	char	quote;
	int		i;

	i = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	get_parsed_line_lenght(char *line)
{
	char	quote;
	int		add;
	int		i;

	i = 0;
	add = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
		}
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			add += 2;
			if (line[i + 1] && line[i + 1] != '|' && line[i + 1] == line[i])
				i++;
		}
		i++;
	}
	return (i + add);
}

static char	*set_parsed_line(char *line, char *new, int i, int j)
{
	char	quote;

	while (line[i])
	{
		if (is_quote(line[i]))
		{
			quote = line[i];
			new[j++] = line[i++];
			while (line[i] && line[i] != quote)
				new[j++] = line[i++];
			new[j++] = line[i++];
		}
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (line[i] && line[i] != '|' && line[i] == line[i - 1])
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	return (new);
}

char	*parse_line(t_line *line, t_arg *data, t_var *lst_var)
{
	char	*new;

	if (quotes_unclosed(line->line))
	{
		write(2, "syntax error: unclosed quote\n", 29);
		free_before_exit(line, data, lst_var);
	}
	new = ft_calloc(sizeof(char), get_parsed_line_lenght(line->line) + 1);
	if (!new)
	{
		write(2, "Error malloc\n", 13);
		free_before_exit(line, data, lst_var);
	}
	new = set_parsed_line(line->line, new, 0, 0);
	if (!new)
	{
		write(2, "Error malloc\n", 13);
		free_before_exit(line, data, lst_var);
	}
	return (new);
}
