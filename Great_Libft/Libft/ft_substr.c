/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgarnier <mgarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:57:56 by jodone            #+#    #+#             */
/*   Updated: 2026/01/26 13:40:43 by mgarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	leng;
	unsigned int	lensrc;

	if (!s)
		return (NULL);
	leng = len;
	lensrc = ft_strlen(s);
	if (start >= lensrc)
	{
		result = malloc(sizeof(char));
		if (!result)
			return (NULL);
		result[0] = '\0';
		return (result);
	}
	if (len > lensrc - start)
		leng = lensrc - start;
	result = ft_calloc(sizeof(char), leng + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, (char *)s + start, leng + 1);
	return (result);
}
