/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:40:44 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 14:42:39 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == 0)
		return ((char *)big);
	while ((i < len) && (*big != 0))
	{
		if (big[0] == little[0])
		{
			j = 0;
			while (little[j] && big[j] && (i + j) < len)
			{
				if (little[j] != big[j])
					break ;
				j++;
				if (little[j] == 0)
					return ((char *)big);
			}
		}
		big++;
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int main(void)
{
    char *haystack = "Very secret hidden text";
    char *needle = "";
    char *location;
    size_t size = 4;

    location = ft_strnstr(haystack, needle, size);
    if(location == NULL)
        puts("Unable to find string with strnstr().");
    else
        printf("%s\n", location);
    return(0);
}
*/
