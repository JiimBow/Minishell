/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:24:04 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 12:17:16 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_unclosed(char *line)
{
	char	quote;
	int		i;

	i = 0;
	while (line && line[i])
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

int	syntax_error(char *line, char token, char quote, size_t i)
{
	i = skip_spaces(line, i);
	while (i < ft_strlen(line) + 1 && line[i])
	{
		if (is_quote(line[i]))
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
		}
		else if (is_operator(line[i]) && line[i] != '|')
		{
			token = line[i++];
			if ((line[i] == '>' || line[i] == '<') && token == line[i])
				i++;
			i = skip_spaces(line, i);
			if (line[i] && token == '|' && (line[i] == '>' || line[i] == '<'))
				continue ;
			if (line[i] == '\0' || is_operator(line[i]))
				return (i - 1);
		}
		i++;
	}
	return (0);
}

int	get_parsed_line_lenght(char *line)
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
		else if (is_operator(line[i]))
		{
			add += 2;
			if (line[i + 1] && line[i + 1] != '|' && line[i + 1] == line[i])
				i++;
		}
		i++;
	}
	return (i + add);
}

char	*set_parsed_line(char *line, char *new, int i, int j)
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
		else if (is_operator(line[i]))
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

int	parse_pipe(t_line *line, char quote, int *pipe_error_block)
{
	int	i;

	i = 0;
	i = skip_spaces(line->new, i);
	if (line->new[i] && line->new[i] == '|')
		return (1);
	while (line->new && line->new[i])
	{
		if (is_quote(line->new[i]))
		{
			quote = line->new[i++];
			while (line->new[i] && line->new[i] != quote)
				i++;
		}
		if (line->new[i] == '|')
		{
			(*pipe_error_block)++;
			i = skip_spaces(line->new, i + 1);
			if ((line->new[i] && line->new[i] == '|') || !line->new[i])
				return (1);
		}
		else
			i++;
	}
	return (0);
}
