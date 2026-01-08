/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:50:13 by jodone            #+#    #+#             */
/*   Updated: 2026/01/08 17:57:31 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <linux/limits.h>

enum token
{
	BUILT_IN,
	COMMAND,
	OPTION,
	FILE,
	DIRECTORY,
	PONCTUATION
};

typedef struct s_arg
{
	int			index;
	char		*content;
	enum  token group;
}	t_arg;

void	process(char **cmd, char **envp);
void	pointer_free(char **str);
char	*find_path(char *cmd, char **envp, int i, char *full_path);
char	**parse_line(char *line);
char	**ft_split_line(char const *s, char c, unsigned int line, int i);
int		ft_pwd(void);

#endif