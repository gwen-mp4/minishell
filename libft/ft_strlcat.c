/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:20:47 by gwen              #+#    #+#             */
/*   Updated: 2025/11/07 11:40:16 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	src_len;
	size_t	dest_len;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (dest_len >= destsize)
		return (src_len + destsize);
	if (src_len < destsize - dest_len)
		ft_memcpy(dest + dest_len, src, src_len + 1);
	else
	{
		ft_memcpy(dest + dest_len, src, destsize - dest_len - 1);
		dest[destsize - 1] = '\0';
	}
	return (dest_len + src_len);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	dest[20] = "Hello";
	const char	*src = "world";
	size_t	n1 = ft_strlcat(dest, src, sizeof(dest));
	char	small[10] = "Hello";
	size_t	n2 = ft_strlcat(small, src, sizeof(small));
	char	empty[10] = "";
	size_t	n3 = ft_strlcat(empty, src, sizeof(empty));
	char	zero[5] = "abcd";
	size_t	n4 = ft_strlcat(zero, src, 0);

	printf("%s, %zu\n", dest, n1);
	printf("%s, %zu\n", small, n2);
	printf("%s, %zu\n", empty, n3);
	printf("%s, %zu\n", zero, n4);

	return (0);
}
	*/