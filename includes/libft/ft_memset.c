/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:02:28 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 14:48:28 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t count)
{
	char	*d;
	size_t	i;

	d = (char *)dest;
	i = 0;
	while (i < count)
	{
		d[i] = (char)c;
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[50] = "/!\\ gogo test /!\\";
       	printf("\nBefore memset(): %s\n", str);

	ft_memset(str + 4, 'X', 4*sizeof(char));

	printf("After memset():  %s\n", str);
	return 0;
}
*/
