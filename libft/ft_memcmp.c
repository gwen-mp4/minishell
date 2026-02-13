/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:30:45 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 14:46:41 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*new_s1;
	unsigned char	*new_s2;

	new_s1 = (unsigned char *)s1;
	new_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (new_s1[i] != new_s2[i])
			return (new_s1[i] - new_s2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main() {
    int res = 0;
    char s1[10] = "geeks";
    char s2[10] = "geeks";

    // Use memcmp() to compare s1 and s2 up to
  	// length of s1
    res = ft_memcmp(s1, s2, 20);

    // Check the result of memcmp
    if (res > 0)
        printf("s1 is greater");
    else if (res < 0)
        printf("s2 is greater");
    else
        printf("both are equal");

    return 0;
}
*/
