/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:30:58 by jodone            #+#    #+#             */
/*   Updated: 2026/01/14 19:15:15 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_lstsize_var(t_var *lst)
{
	int	count;

	count = 0;
	if (lst)
	{
		while (lst)
		{
			count++;
			lst = lst->next;
		}
	}
	return (count);
}

t_var	*ft_lst_new_var(char *name, char *content)
{
	t_var	*newnode;

	newnode = malloc(sizeof(t_var));
	if (!newnode)
		return (NULL);
	newnode->name = ft_strdup(name);
	newnode->content = ft_strdup(content);
	newnode->next = NULL;
	return (newnode);
}

t_var	*ft_lstlast_var(t_var *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_var(t_var **lst, t_var *new)
{
	t_var	*tmp;

	if (!lst)
		return ;
	tmp = ft_lstlast_var(*lst);
	if (!tmp)
		*lst = new;
	else
		tmp->next = new;
}

void	ft_lstclear_var(t_var **lst, void (*del)(void *))
{
	t_var	*list;
	t_var	*tmp;

	if (!*lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		tmp = list->next;
		del(list->content);
		del(list->name);
		free(list);
		list = tmp;
	}
	free(list);
	*lst = NULL;
}
