/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 13:04:05 by jodone            #+#    #+#             */
/*   Updated: 2026/01/22 13:08:45 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*add_nl(char *limiter)
{
	int		len;
	char	*new_lim;

	len = ft_strlen(limiter);
	new_lim = ft_calloc(len + 2, sizeof(char));
	if (!new_lim)
		return (NULL);
	new_lim = ft_strdup(limiter);
	ft_strlcat(new_lim, "\n", len + 2);
	return (new_lim);
}
