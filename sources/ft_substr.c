/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 08:44:55 by mgarnier          #+#    #+#             */
/*   Updated: 2026/01/08 10:22:38 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
	{
		tab = (char *)malloc(sizeof(char));
		if (!tab)
			return (NULL);
		tab[0] = '\0';
		return (tab);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	tab = (char *)malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, (char *)s + start, len + 1);
	return (tab);
}
