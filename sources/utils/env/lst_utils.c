/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:30:58 by jodone            #+#    #+#             */
/*   Updated: 2026/01/27 18:17:09 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_var	*ft_lst_new_var(char *name, char *content, int index)
{
	t_var	*newnode;

	newnode = malloc(sizeof(t_var));
	if (!newnode)
		return (NULL);
	newnode->name = ft_strdup(name);
	newnode->content = ft_strdup(content);
	newnode->rank = -1;
	newnode->index = index;
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

	if (!lst || !*lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		tmp = list->next;
		if (list->content)
			del(list->content);
		if (list->name)
			del(list->name);
		free(list);
		list = tmp;
	}
	if (list)
		free(list);
	*lst = NULL;
}
