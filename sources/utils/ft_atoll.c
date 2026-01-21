/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodone <jodone@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:23:51 by jodone            #+#    #+#             */
/*   Updated: 2026/01/21 19:21:25 by jodone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static long	of_atoll(const char *nptr, t_atoll *atol, int i, int *overf)
{
	if (atol->sign > 0 && atol->result > atol->result * 10 + (nptr[i] - 48))
		*overf = -1;
	else if (atol->sign < 0
		&& atol->result * -1 < (atol->result * 10 + (nptr[i] - 48)) * -1)
		*overf = -1;
	atol->result = atol->result * 10 + (nptr[i] - 48);
	return (atol->result);
}

long	ft_atoll(const char *nptr, int *overf)
{
	t_atoll	atol;
	int		i;

	atol.sign = 1;
	atol.result = 0;
	i = 0;
	if (!nptr || !*nptr)
		return (0);
	while (nptr && (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			atol.sign *= -1;
		i++;
	}
	while (nptr && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		atol.result = of_atoll(nptr, &atol, i, overf);
		if ((nptr[i + 1] < '0' || nptr[i + 1] > '9') || atol.result < 0)
			return (atol.result * atol.sign);
		i++;
	}
	return (atol.result);
}
