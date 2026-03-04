/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:03:34 by gwen              #+#    #+#             */
/*   Updated: 2025/11/07 13:03:36 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return ((void *)dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	*str = "Hello world!";
	char	dest[20];
	char	dest2[20];

	printf("%s\n", str);

	ft_memcpy(dest, str, 5);
	dest[5] ='\0';
	printf("%s\n", dest);

	memcpy(dest2, str, 5);
	dest[5] = '\0';
	printf("%s\n", dest2);

	return (0);
}
	*/