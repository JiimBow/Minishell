/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 11:52:55 by jodone            #+#    #+#             */
/*   Updated: 2026/01/13 18:05:49 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		i++;
	}
	free(tab);
	tab = NULL;
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**args;
	int		sig_return;
	t_arg	*data;
	t_env	*env;

	(void)argc;
	(void)argv;
	args = NULL;
	env = ft_get_env(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("minishell> ");
		if (!line || ft_strncmp(line, "exit", 5) == 0)
		{
			free(line);
			printf("exit\n");
			rl_clear_history();
			free_double_tab(env->env);
			free(env);
			exit(0);
		}
		else
		{
			args = ft_split_line(env->env, line, ' ', 0, 0);
			data = tokenisation(args, 0);
			if (args && args[0] && ft_strncmp(args[0], "cd", 3) == 0)
				ft_cd(args, env->env);
			else if (args && args[0] && ft_strncmp(args[0], "pwd", 4) == 0)
				ft_pwd();
			else if (args && args[0] && !args[1]
				&& ft_strncmp(args[0], "env", 4) == 0)
				ft_env(env->env);
			else if (args && args[0] && ft_strncmp(args[0], "echo", 5) == 0)
				ft_echo(args);
			else if (args && args[0] && ft_strncmp(args[0], "unset", 6) == 0)
				ft_unset(env, args);
			else
				sig_return = process(args, env);
			free_double_tab(args);
			free_struct(data);
		}
		add_history(line);
		free(line);
	}
	return (0);
}
