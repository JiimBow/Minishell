/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:24:04 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/26 14:59:30 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_unclosed(char *line)
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

static int	syntax_error(char *line, char token, char quote, size_t i)
{
	i = skip_spaces(line, i);
	if (line[i] && line[i] == '|')
		return (i);
	while (i < ft_strlen(line) + 1 && line[i])
	{
		if (is_quote(line[i]))
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
		}
		else if (is_operator(line[i]))
		{
			token = line[i++];
			if ((line[i] == '>' || line[i] == '<') && token == line[i])
				i++;
			i = skip_spaces(line, i);
			if (line[i] && token == '|' && (line[i] == '>' || line[i] == '<'))
				continue ;
			if (line[i] == '\0' || is_operator(line[i]))
				return (i - 2);
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

char	*parse_line(t_line *line, t_var *lst_var)
{
	char	*new;
	int		syntax;

	if (quotes_unclosed(line->line))
	{
		write(2, "minishell: syntax error unclosed quote\n", 39);
		line->sig = 2;
		return (NULL);
	}
	new = ft_calloc(sizeof(char), get_parsed_line_lenght(line->line) + 1);
	if (!new)
		error_memory_failed(line, lst_var);
	new = set_parsed_line(line->line, new, 0, 0);
	syntax = syntax_error(new, 't', 'q', 0);
	if (syntax != 0)
	{
		write(2, "minishell: syntax error near unexpected token \" ", 48);
		write(2, &new[syntax], 1);
		write(2, " \"\n", 3);
		free(new);
		line->sig = 2;
		return (NULL);
	}
	return (new);
}
