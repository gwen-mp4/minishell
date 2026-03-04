/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:11:27 by gwen              #+#    #+#             */
/*   Updated: 2025/11/07 11:20:22 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!destsize)
		return (src_len);
	while (src[i] && i < destsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}
/*
#include <stdio.h>
#include <string.h>

int main() 
{
	char	src[] = "HelloWorld";
	char	dest[20];
	size_t ret = ft_strlcpy(dest, src, sizeof(dest));

	printf("Original: %s\n", src);
	printf("Ma fonction: %s, retour = %zu\n", dest, ret);

	char	small[6];
	size_t ret2 = ft_strlcpy(small, src,sizeof(small));
	printf("small: %s\n", small);
	printf("len: %zu\n", ret2);

	char	empty[5] = "abcd";
	size_t ret3 = ft_strlcpy(empty, src, 0);
	printf("empty: %s\n", empty);
	printf("len: %zu\n", ret3);

	return (0);
}
	*/