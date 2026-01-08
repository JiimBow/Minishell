/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:20 by jodone            #+#    #+#             */
/*   Updated: 2026/01/08 22:34:36 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int		i;
	const unsigned char	*result;

	i = 0;
	result = s;
	while (i < n)
	{
		if (result[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
