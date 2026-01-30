/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:56:57 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/30 16:40:13 by mgarnier         ###   ########.fr       */
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

static int	variable_with_spaces(t_line *line, char *arg)
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
		if (is_quote(arg[i]))
		{
			char	quote = arg[i++];
			while (arg[i] && arg[i] != quote)
				i++;
		}
		else if (arg[i] == '$' && arg[i + 1]
			&& (arg[i + 1] == '_' || ft_isalnum(arg[i + 1])))
		{
			name = get_name(arg + i + 1);
			content = get_content(line->env, name);
			j = 0;
			while (content && content[j])
			{
				j = skip_spaces(content, j);
				save_j = j;
				j = skip_word(content, j);
				if (j > save_j)
					count++;
			}
			if (content)
				count--;
			free(name);
			free(content);
		}
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

static char	**reduce_args(t_line *line, t_var *lst_var, int *size)
{
	char	**new_args;
	int		len;
	int		i;

	if (!line->args)
		return (NULL);
	len = count_size_no_redirection(line, lst_var);
	*size = len;
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

void	replace_args_without_redirection(t_line *line, t_var *lst_var)
{
	char	**new_args;
	char	*tmp;
	int		i;
	int		size;

	size = 0;
	line->args = reduce_args(line, lst_var, &size);
	// ft_printf("size=%d\n", size);
	i = 0;
	while (line->args && line->args[i])
	{
		tmp = substr_var_unquote(line, lst_var, line->args[i]);
		line->args[i] = ft_strdup(tmp);
		// if (expand == 1)
			// fonction qui change line-args; <----------------------------------------------------
		free(tmp);
		i++;
	}
	new_args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_args)
		error_memory_failed(line, lst_var);
	i = 0;
	while (line->args && line->args[i])
	{
		//remplir le new_args en fonction des variables
		
		i++;
	}
	free(new_args);
}
