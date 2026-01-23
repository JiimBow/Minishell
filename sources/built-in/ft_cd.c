/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:44:39 by jodone            #+#    #+#             */
/*   Updated: 2026/01/23 23:00:02 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_path(t_var *lst_var, char *str)
{
	t_var	*tmp;
	int		len_str;

	tmp = lst_var;
	len_str = ft_strlen(str) + 1;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->name, len_str) == 0)
			return (tmp->content);
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

int	ft_cd(t_line *line, t_var *lst_var)
{
	char	*path;

	if (line->args[2])
	{
		write(2, "minishell: cd: too many arguments\n", 34);
		return (1);
	}
	if (!line->args[1] || ft_strncmp(line->args[1], "~", 2) == 0)
		path = get_env_path(lst_var, "HOME");
	else
		path = line->args[1];
	update_path(lst_var, 1);
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 15);
		perror(path);
		return (1);
	}
	update_path(lst_var, 0);
	return (0);
}
