/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 18:24:04 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/15 20:29:08 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_name(const char *s)
// {
// 	char	*name;
// 	int		i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
// 		i++;
// 	name = (char *)malloc(sizeof(char) * (i + 1));
// 	if (!name)
// 		return (NULL);
// 	i = 0;
// 	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
// 	{
// 		name[i] = s[i];
// 		i++;
// 	}
// 	name[i] = '\0';
// 	return (name);
// }

// static char	*get_content(char **env, char *tab)
// {
// 	char	*content;
// 	int		size_tab;
// 	int		i;

// 	if (!env || !tab)
// 		return (NULL);
// 	size_tab = ft_strlen(tab);
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], tab, size_tab) == 0 && env[i][size_tab] == '=')
// 		{
// 			content = ft_strdup(env[i] + size_tab + 1);
// 			return (content);
// 		}
// 		i++ ;
// 	}
// 	return (NULL);
// }

// static int	get_count(char **env, const char *s, int *i)
// {
// 	char	*name;
// 	char	*content;
// 	int		count;

// 	if (!env || !*env || !s)
// 		return (0);
// 	count = 0;
// 	name = get_name(s);
// 	content = get_content(env, name);
// 	if (content)
// 	{
// 		count = ft_strlen(content);
// 		*i += ft_strlen(name);
// 	}
// 	free(name);
// 	free(content);
// 	return (count);
// }

// static int	ft_intlen(int n)
// {
// 	int	i;

// 	i = 0;
// 	while (n > 0)
// 	{
// 		n /= 10;
// 		i++;
// 	}
// 	return (i);
// }

// static int	variable_size(t_line *line, int *i, int count)
// {
// 	if (line->line[*i + 1] == '?')
// 	{
// 		count = ft_intlen(g_sig);
// 		(*i)++;
// 	}
// 	else if (line->line[*i + 1] == '_' || ft_isalpha(line->line[*i + 1]))
// 		count = get_count(line->env, line->line + *i + 1, i);
// 	else
// 		count = 1;
// 	(*i)++;
// 	return (count);
// }

char	*parse_line(t_line *line)
{
	char	*new;
	// char	quote;
	// int		size;
	// int		i;

	new = substr_var(line->env, line->line, ft_strlen(line->line));
	// i = 0;
	// size = 0;
	// while (line->line[i])
	// {
	// 	if (is_quote(line->line[i]))
	// 	{
	// 		quote = line->line[i++];
	// 		size++;
	// 		while (line->line[i] && line->line[i] != quote)
	// 		{
	// 			if (quote == '"' && line->line[i] == '$' && line->line[i + 1])
	// 				size += variable_size(line, &i, 0);
	// 			else
	// 			{
	// 				size++;
	// 				i++;
	// 			}
	// 		}
	// 		if (line->line[i] && line->line[i] == quote)
	// 		{
	// 			size++;
	// 			i++;
	// 		}
	// 		else
	// 		{
	// 			write(2, "minishell: syntax error\n", 24);
	// 			g_sig = 2;
	// 			return (NULL);
	// 		}
	// 	}
	// 	else if (line->line[i] == '$' && line->line[i + 1])
	// 		size += variable_size(line, &i, 0);
	// 	else
	// 	{
	// 		size++;
	// 		i++;
	// 	}
	// }
	printf("len=%zu%s\n", new);
	// new = (char *)malloc(sizeof(char) * (size + 1));
	// if (!new)
	// 	return (NULL);
	return (new);
}
