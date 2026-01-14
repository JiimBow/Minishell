/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:05:31 by jodone            #+#    #+#             */
/*   Updated: 2026/01/14 16:47:37 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_print(char *s, int fd, int *count)
{
	if (!s)
	{
		if (write(fd, "(null)", 6) != -1)
			(*count) += 6;
	}
	else
	{
		if (write(fd, s, print_strlen(s)) != -1)
			(*count) += print_strlen(s);
	}
}
