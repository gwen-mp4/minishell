/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:09:54 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 14:41:31 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (ft_strlen(src) == 0)
	{
		dst[0] = '\0';
		return (0);
	}
	if (siz != 0)
	{
		while (i < siz - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	len = ft_strlen(src);
	return (len);
}
/*
#include <stdio.h>
#include <strings.h>

int	main(void)
{
	const char	from[20] = "Fleur de lys";
	char	to[20];
	int	l = ft_strlcpy(to, from, 5);

	printf("%d\n", l);
	printf("%s\n", to);
	return (0);
}
*/
