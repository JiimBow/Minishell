/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:52:55 by jodone            #+#    #+#             */
/*   Updated: 2026/01/15 09:32:30 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_sig = 0;

void	free_struct(t_arg *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (data[i].group != END)
	{
		if (data[i].content)
			free(data[i].content);
		data[i].content = NULL;
		i++;
	}
	free(data);
	data = NULL;
}

void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

static void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
		if (WIFSIGNALED(signal))
			g_sig = WTERMSIG(signal) + 128;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	*data;
	t_env	*env;
	t_line	*line;
	t_var	*lst_var;

	(void)argc;
	(void)argv;
	line = (t_line *)malloc(sizeof(t_line));
	if (!line)
		return (1);
	lst_var = NULL;
	get_var(&lst_var, envp);
	env = ft_get_env(&lst_var);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line->args = NULL;
		line->line = readline("minishell> ");
		if (!line->line)
			free_before_exit(line, env, NULL, lst_var);
		else
		{
			line->args = ft_split_line(env->env, line->line);
			data = NULL;//tokenisation(line->args, 0);
			if (line->args && line->args[0]
				&& ft_strncmp(line->args[0], "cd", 3) == 0)
				g_sig = ft_cd(line->args, env->env);
			else if (line->args && line->args[0]
				&& ft_strncmp(line->args[0], "pwd", 4) == 0)
				g_sig = ft_pwd(env);
			else if (line->args && line->args[0] && !line->args[1]
				&& ft_strncmp(line->args[0], "env", 4) == 0)
				g_sig = ft_env(env->env);
			else if (line->args && line->args[0]
				&& ft_strncmp(line->args[0], "echo", 5) == 0)
				g_sig = ft_echo(line->args);
			else if (line->args && line->args[0]
				&& ft_strncmp(line->args[0], "unset", 6) == 0)
				g_sig = ft_unset(env, line->args);
			else if (line->args && line->args[0]
				&& ft_strncmp(line->args[0], "exit", 5) == 0)
				g_sig = free_before_exit(line, env, data, lst_var);
			else
				g_sig = process(line->args, env);
			free_double_tab(line->args);
			free_struct(data);
			add_history(line->line);
			free(line->line);
			line->line = NULL;
		}
	}
	return (0);
}
