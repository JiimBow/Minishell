/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:52:55 by jodone            #+#    #+#             */
/*   Updated: 2026/01/22 10:34:59 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	g_sig = 0;

static void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_printf("\n");
		rl_redisplay();
		if (WIFSIGNALED(signal))
			g_sig = WTERMSIG(signal) + 128;
	}
}

void	assignement(t_line *line, t_var *lst_var, int is_fork)
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
		g_sig = free_before_exit(line, lst_var);
	else if (line->args && line->args[0]
		&& ft_strncmp(line->args[0], "export", 7) == 0)
		g_sig = ft_export(&lst_var, line->args);
	else if (line->args)
		g_sig = process(line, lst_var, 0, is_fork);
}

static void	get_last_status(__pid_t pid, __pid_t last_pid)
{
	int	last_status;
	int	status;

	while (pid > 0)
	{
		if (pid == last_pid)
			last_status = status;
		pid = wait(&status);
	}
	g_sig = return_value(last_status);
}

static void	minishell(t_line *line, t_var *lst_var, t_pipe child, int i)
{
	__pid_t	pid;
	__pid_t	last_pid;
	char	*tmp;

	line->new = parse_line(line);
	line->block = split_pipe(line);
	while (line->block && line->block[i])
	{
		pid = 1;
		child.index = i + 1;
		tmp = ft_substr(line->block[i], 0, ft_strlen(line->block[i]));
		free(line->block[i]);
		line->block[i] = substr_var(line->env, tmp);
		free(tmp);
		line->args = split_line(line->block[i]);
		// int	j = 0;
		// ft_printf("block[%d]=>\n", i);
		// while (line->args && line->args[j])
		// {
		// 	ft_printf("AVANT/args[%d]=%s\n", j, line->args[j]);
		// 	j++;
		// }
		find_redirection(line);
		// j = 0;
		// ft_printf("---\n");
		// while (line->args && line->args[j])
		// {
		// 	ft_printf("APRES/args[%d]=%s\n", j, line->args[j]);
		// 	j++;
		// }
		// ft_printf("---\n");
		// if (line && line->red)
		// {
		// 	t_var	*tmp = line->red;
		// 	while (tmp)
		// 	{
		// 		ft_printf("line->red->content=%s\nline->red->rank=%d\n",
		// 			tmp->content, tmp->rank);
		// 		tmp = tmp->next;
		// 	}
		// }
		// ft_printf("==========\n");
		if (line->row > 1)
			last_pid = pipe_process(line, lst_var, &child);
		else
			assignement(line, lst_var, 0);
		free_double_tab(line->args);
		line->args = NULL;
		i++;
	}
	if (line->row > 1)
		get_last_status(pid, last_pid);
}

void	init_struct(t_line *line, t_var *lst_var, t_pipe *child)
{
	line->env = ft_copy_env(&lst_var);
	line->args = NULL;
	line->block = NULL;
	line->red = NULL;
	*child = pipe_init();
}

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	t_var	*lst_var;
	t_pipe	child;

	(void)argc;
	(void)argv;
	lst_var = NULL;
	get_var(&lst_var, envp);
	line = creation_line();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		init_struct(line, lst_var, &child);
		line->line = readline("minishell> ");
		if (!line->line)
			free_before_exit(line, lst_var);
		else
		{
			minishell(line, lst_var, child, 0);
			add_history(line->line);
			free_line_struct(line, 0);
		}
	}
	return (0);
}
