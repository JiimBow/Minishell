/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:44:39 by jodone            #+#    #+#             */
/*   Updated: 2026/02/10 17:37:20 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_path(t_var *lst_var, char *str)
{
	t_var	*tmp;
	int		len_str;
	char	*new_path;

	tmp = lst_var;
	len_str = ft_strlen(str);
	while (tmp)
	{
		if (ft_strncmp(str, tmp->name, len_str + 1) == 0)
		{
			new_path = ft_strdup(tmp->content);
			return (new_path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void	replace_content(t_var *lst_var, char *name, char *new_content)
{
	t_var	*tmp;
	int		len_old;

	tmp = lst_var;
	len_old = ft_strlen(name);
	while (tmp)
	{
		if (ft_strncmp(name, tmp->name, len_old + 1) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(new_content);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	update_path(t_var *lst_var, int is_old)
{
	char	curr_path[PATH_MAX];

	getcwd(curr_path, sizeof(curr_path));
	if (is_old == 1)
		replace_content(lst_var, "OLDPWD", curr_path);
	else
		replace_content(lst_var, "PWD", curr_path);
}

static char	*get_path(t_line *line, t_var *lst_var)
{
	char	*path;

	path = NULL;
	if (!line->args[1])
		path = get_env_path(lst_var, "HOME");
	else if (ft_strncmp(line->args[1], "~", 1) == 0)
	{
		path = ft_strdup(line->home);
		if (line->args[1] && line->args[1][1])
			path = gnl_strjoin(path, line->args[1] + 1);
	}
	else if (ft_strncmp(line->args[1], ".", 2) == 0)
		path = get_env_path(lst_var, "PWD");
	else
		path = ft_strdup(line->args[1]);
	return (path);
}

int	ft_cd(t_line *line, t_var *lst_var)
{
	char	*path;

	if (line->args[1] && line->args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	path = get_path(line, lst_var);
	if (!path)
		return (0);
	update_path(lst_var, 1);
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		perror(path);
		free(path);
		return (1);
	}
	update_path(lst_var, 0);
	free(path);
	return (0);
}
