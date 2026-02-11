/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:33:17 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 14:39:46 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t n)
{
	const unsigned char	*source;
	unsigned char		*dest;
	long				i;

	source = (const unsigned char *)src;
	dest = (unsigned char *)dst;
	if (!dest && !src && n)
		return (dest);
	i = n;
	if (dest >= source)
	{
		while (--i >= 0)
			dest[i] = source[i];
	}
	else
	{
		i = 0;
		while ((size_t)i < n)
		{
			dest[i] = source[i];
			i++;
		}
	}
	return (dst);
}
/*
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	char a[50]="hare rama hare rama";

	char b[50]="hare rama hare rama";

	ft_memmove(a+5,a,20);
	puts(a);

	memmove(b+5,b,20);
	puts(b);
}
*/
