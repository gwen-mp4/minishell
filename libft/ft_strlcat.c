/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 14:49:56 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 14:41:07 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (siz == 0)
		return (src_len);
	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (j + i < siz - 1 && src[j])
	{
		dst[j + i] = src[j];
		j++;
	}
	if (siz <= dst_len)
		return (src_len + siz);
	else
	{
		dst[i + j] = '\0';
		return (src_len + dst_len);
	}
}
/*
#include <stdio.h>
#include <bsd/string.h>

int main()
{
	char first[] = "This is ";
	char last[] = "a potentially long string";
	int r;
	int size = 0;

	r = ft_strlcat(buffer,last,size);

	puts(buffer);
	printf("Value returned: %d\n",r);
	return(0);
}
*/
