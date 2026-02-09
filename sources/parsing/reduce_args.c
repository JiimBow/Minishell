/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 13:29:08 by mgarnier          #+#    #+#             */
/*   Updated: 2026/02/09 14:52:11 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	count_variable_size(t_line *line, char *arg)
{
	char	*name;
	char	*content;
	int		i;
	int		save_i;
	int		count;

	name = get_name(arg);
	content = get_content(line->env, name);
	i = 0;
	count = 0;
	while (content && content[i])
	{
		i = skip_spaces(content, i);
		save_i = i;
		i = skip_word(content, i);
		if (i > save_i)
			count++;
	}
	if (content)
		count--;
	free(name);
	free(content);
	return (count);
}

static int	variable_with_spaces(t_line *line, char *arg)
{
	char	quote;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (arg[i])
	{
		if (is_quote(arg[i]))
		{
			quote = arg[i++];
			while (arg[i] && arg[i] != quote)
				i++;
		}
		else if (arg[i] == '$' && arg[i + 1]
			&& (arg[i + 1] == '_' || ft_isalnum(arg[i + 1])))
			count += count_variable_size(line, arg + i + 1);
		if (arg[i])
			i++;
	}
	return (count);
}

static int	count_size_no_redirection(t_line *line, t_var *lst_var)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line->args[i])
	{
		if (is_redirection(line->args[i]))
		{
			i++;
			count -= 2;
		}
		else if (variable_not_existed(line, lst_var, line->args[i]))
			count--;
		else
			count += variable_with_spaces(line, line->args[i]);
		i++;
	}
	return (i + count);
}

char	**reduce_args_without_redirection(t_line *line, t_var *lst_var)
{
	char	**new_args;
	int		len;
	int		i;

	if (!line->args)
		return (NULL);
	len = count_size_no_redirection(line, lst_var);
	new_args = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_args)
		error_memory_failed(line, lst_var);
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
	new_args[len] = NULL;
	free_double_tab(line->args);
	return (new_args);
}

void	replace_variables(t_line *line, t_var *lst_var)
{
	int	i;

	i = 0;
	while (line->args[i])
	{
		line->args[i] = substr_var_unquote(line, lst_var, line->args[i]);
		i++;
	}
}
