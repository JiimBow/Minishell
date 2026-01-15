/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:06:58 by jodone            #+#    #+#             */
/*   Updated: 2026/01/14 16:45:37 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_bzero(void *s, size_t n)
{
	unsigned long	i;
	unsigned char	*result;

	i = 0;
	result = (void *)s;
	while (i < n)
	{
		result[i] = '\0';
		i++;
	}
}
