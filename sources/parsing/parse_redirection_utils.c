/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:52:52 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 11:21:29 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	variable_not_existed(t_line *line, t_var *lst_var, char *tab)
{
	char	*tmp;

	tmp = ft_substr(tab, 0, ft_strlen(tab));
	tmp = substr_var(line, lst_var, tmp);
	if (tmp && tmp[0] == '\0')
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	variable_with_spaces(t_line *line, t_var *lst_var, char *arg, int *pos)
{
	char	*name;
	char	*content;
	int		count;
	int		i;
	int		j;
	int		save_j;

	count = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1]
			&& (arg[i + 1] == '_' || ft_isalnum(arg[i + 1])))
		{
			name = get_name(arg + i + 1);
			if (!name)
				error_memory_failed(line, lst_var);
			content = get_content(line->env, name);
			if (!content)
				error_memory_failed(line, lst_var);
			j = 0;
			while (content[j])
			{
				j = skip_spaces(content, j);
				save_j = j;
				j = parse_word(content, j);
				if (j > save_j)
					count++;
			}
			*pos += i + ft_strlen(name);
			free(name);
			free(content);
			break;
		}
		i++;
	}
	return (count);
}

static int	count_size_no_redirection(t_line *line, t_var *lst_var, int *i)
{
	int	count;

	count = 0;
	while (line->args[*i])
	{
		if (is_redirection(line->args[*i]))
		{
			(*i)++;
			count -= 2;
		}
		else if (variable_not_existed(line, lst_var, line->args[*i]))
			count--;
		else
			count += variable_with_spaces(line, lst_var, line->args[*i], i);
		(*i)++;
	}
	return (count);
}

static char	**reduce_args(t_line *line, t_var *lst_var, int i)
{
	char	**new_args;
	int		len;

	if (!line->args)
		return (NULL);
	len = count_size_no_redirection(line, lst_var, &i);
	ft_printf("nb de arg=%d\n", i + len);
	new_args = (char **)malloc(sizeof(char *) * (i + len + 1));
	if (!new_args)
		error_memory_failed(line, lst_var);
	new_args[i - len] = NULL;
	i = 0;
	len = 0;
	while (line->args[i])
	{
		if (is_redirection(line->args[i]))
			i += 2;
		else if (variable_not_existed(line, lst_var, line->args[i]))
			i++;
		else
			new_args[len++] = ft_strdup(line->args[i++]);
	}
	free_double_tab(line->args);
	return (new_args);
}

void	replace_args_without_redirection(t_line *line, t_var *lst_var)
{
	char	*tmp;
	int		i;
	int		expand;

	line->args = reduce_args(line, lst_var, 0);
	i = 0;
	while (line->args && line->args[i])
	{
		expand = 0;
		tmp = substr_var_unquote(line, lst_var, line->args[i], &expand);
		line->args[i] = ft_strdup(tmp);
		// if (expand == 1)
			// fonction qui change line-args; <----------------------------------------------------
		free(tmp);
		i++;
	}
}

char	*strdup_unquote(t_line *line, t_var *lst_var, char *s, int j)
{
	char	*new;
	char	quote;
	int		n;
	int		i;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	new = ft_calloc(sizeof(char), n + 1);
	if (!new)
		error_memory_failed(line, lst_var);
	i = 0;
	while (i < n)
	{
		if (is_quote(s[i]) && s[i + 1])
		{
			quote = s[i++];
			while (i < n && s[i] != quote)
				new[j++] = s[i++];
			i++;
		}
		else
			new[j++] = s[i++];
	}
	return (new);
}
