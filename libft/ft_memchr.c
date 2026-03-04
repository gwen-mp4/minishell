/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:34:47 by gwen              #+#    #+#             */
/*   Updated: 2025/11/07 13:34:48 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	occ;
	size_t			i;

	str = (unsigned char *)s;
	occ = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == occ)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
