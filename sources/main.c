/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:52:55 by jodone            #+#    #+#             */
/*   Updated: 2026/01/20 09:47:48 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

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

static void	assignement(t_line *line, t_var *lst_var, t_arg *data)
{
	if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "cd", 3) == 0)
		g_sig = ft_cd(line, lst_var);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "pwd", 4) == 0)
		g_sig = ft_pwd(lst_var);
	else if (line->args && line->args[0] && !line->args[1]
		&& ft_strncmp(line->args[0], "env", 4) == 0)
		g_sig = ft_env(line->env);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "echo", 5) == 0)
		g_sig = ft_echo(line->args);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "unset", 6) == 0)
		g_sig = ft_unset(line, &lst_var);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "exit", 5) == 0)
		g_sig = free_before_exit(line, data, lst_var);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "export", 7) == 0)
		g_sig = ft_export(&lst_var, line->args);
	else if (line->args)
		g_sig = process(line, lst_var, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	*data;
	t_line	*line;
	t_var	*lst_var;

	(void)argc;
	(void)argv;
	lst_var = NULL;
	get_var(&lst_var, envp);
	line = creation_line();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line->env = ft_copy_env(&lst_var);
		line->args = NULL;
		line->block = NULL;
		line->line = readline("minishell> ");
		if (!line->line)
			free_before_exit(line, NULL, lst_var);
		else
		{
			line->new = parse_line(line);
			line->args = split_line(line);
			data = NULL;//tokenisation(line->args, 0);
			assignement(line, lst_var, data);
			add_history(line->line);
			free_line_struct(line, 0);
			line->line = NULL;
			free_struct(data);
		}
	}
	return (0);
}
