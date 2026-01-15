/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:51 by jodone            #+#    #+#             */
/*   Updated: 2026/01/14 18:20:25 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_and_exit(t_line *line, int sig_exit)
{
	free(line->line);
	if (sig_exit || !line->args[1])
	{
		free_double_tab(line->args);
		free(line);
		exit(sig_exit);
	}
	free_double_tab(line->args);
	free(line);
	exit(2);
}

static int	arg_isnum(char *args)
{
	int	i;

	i = 0;
	if (args && (args[0] == '-' || args[0] == '+'))
		i++;
	while (args && args[i])
	{
		if (!ft_isdigit(args[i]))
			return (0);
		i++;
	}
	return (1);
}

int	free_before_exit(t_line *line, t_env *env, t_arg *data, t_var *lst_var)
{
	printf("exit\n");
	if (line->args && line->args[1] && line->args[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	rl_clear_history();
	ft_lstclear_var(&lst_var, free);
	free_double_tab(env->env);
	if (env)
		free(env);
	if (line->args && !arg_isnum(line->args[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, line->args[1], ft_strlen(line->args[1]));
		write(2, ": numeric argument required\n", 29);
	}
	else if (line->args && !g_sig)
		g_sig = ft_atoi(line->args[1]);
	free_struct(data);
	if (line->line)
		free_and_exit(line, g_sig);
	free_double_tab(line->args);
	free(line);
	exit(g_sig);
}
