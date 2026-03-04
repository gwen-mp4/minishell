/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:35:37 by gwen              #+#    #+#             */
/*   Updated: 2025/11/07 14:33:44 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*tmp_dest;
	unsigned char		*tmp_src;

	tmp_dest = (unsigned char *)dest;
	tmp_src = (unsigned char *)src;
	if (!tmp_dest && !tmp_src)
		return (NULL);
	if (tmp_dest > tmp_src)
	{
		while (n > 0)
		{
			tmp_dest[n - 1] = tmp_src[n - 1];
			n--;
		}
	}
	else
		ft_memcpy(tmp_dest, tmp_src, n);
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char	str[] = "0123456789";
	char	str2[] = "0123456789";

	printf("%s\n", str);
	ft_memmove(str + 3, str, 5);
	printf("%s\n", str);
	memmove(str2 + 3, str2, 5);
	printf("%s\n", str2);
	return (0);
}
*/