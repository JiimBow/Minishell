/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:46:45 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/13 10:47:14 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_copy(t_line *line, t_var *lst_var)
{
	char	**copy;
	int		i;

	i = 0;
	while (line->args[i])
		i++;
	copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!copy)
		error_memory_failed(line, lst_var);
	i = 0;
	while (line->args[i])
	{
		copy[i] = ft_strdup(line->args[i]);
		free(line->args[i]);
		line->args[i] = NULL;
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	split_situational(t_line *line, t_var *lst_var, char *word, int *i)
{
	char	**var;
	int		y;

	if (ft_strlen(ft_strchr(word, '='))
		< ft_strlen(ft_strchr(word, ' ')))
		var = split_spaces_unquote(line, lst_var, word);
	else
		var = ft_split(word, '\0');
	if (!var)
		return (-1);
	y = 0;
	while (var && var[y])
	{
		if (y == 0 || ft_strchr(var[0], '='))
			line->args[*i] = gnl_strjoin(line->args[*i], var[y]);
		else
			line->args[++(*i)] = ft_strdup(var[y]);
		y++;
	}
	var = free_double_tab(var);
	return (0);
}

static int	fill_args(t_line *line, t_var *lst_var, char **word, int *i)
{
	int		x;

	x = 0;
	while (word && word[x])
	{
		if (is_quote(word[x][0]))
		{
			word[x] = substr_var_unquote(line, lst_var, word[x]);
			if (!word[x])
				return (-1);
			line->args[*i] = gnl_strjoin(line->args[*i], word[x]);
		}
		else if (ft_strncmp(word[x], "$", 2) == 0 && word[x + 1] != NULL)
			;
		else
		{
			word[x] = substr_var_unquote(line, lst_var, word[x]);
			if (!word[x])
				return (-1);
			if (split_situational(line, lst_var, word[x], i) == -1)
				return (-1);
		}
		x++;
	}
	return (0);
}

void	replace_variables(t_line *line, t_var *lst_var)
{
	char	**copy;
	char	**word;
	int		i;
	int		j;

	copy = create_copy(line, lst_var);
	j = 0;
	i = 0;
	while (copy[j])
	{
		word = split_words(copy[j]);
		if (!word || fill_args(line, lst_var, word, &i) == -1)
		{
			word = free_double_tab(word);
			copy = free_double_tab(copy);
			error_memory_failed(line, lst_var);
		}
		word = free_double_tab(word);
		j++;
		i++;
	}
	line->args[i] = NULL;
	copy = free_double_tab(copy);
}
