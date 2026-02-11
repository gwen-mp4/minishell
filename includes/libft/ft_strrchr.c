/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:49:10 by storck            #+#    #+#             */
/*   Updated: 2025/11/14 12:48:34 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = 0;
	while (*s)
	{
		if (*s == (char)c)
			tmp = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (tmp);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
    // initializing string
    char str[] = "GeesforGees";

    // character to be searched
    char chr = 'k';

    // Storing pointer returned by
    char* ptr = ft_strrchr(str, chr);

    // getting the position of the character
    if (ptr) {
        printf("Last occurrence of %c in %s is at index %ld",
               chr, str, ptr - str);
    }
    // condition for character not present
    else {
        printf("%c is not present in %s ", chr, str);
    }
    return 0;
}
*/
