/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:59:27 by jodone            #+#    #+#             */
/*   Updated: 2026/01/20 18:17:14 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	if_no_path(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror(NULL);
		return (1);
	}
	ft_printf("%s\n", cwd);
	return (0);
}

int	ft_pwd(t_var *lst_var)
{
	char	*path;

	path = get_env_path(lst_var, "PWD");
	if (!path)
	{
		if (if_no_path() == 0)
			return (0);
		return (1);
	}
	else
		ft_printf("%s\n", path);
	return (0);
}
