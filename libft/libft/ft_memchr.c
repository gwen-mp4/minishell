/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:12:34 by storck            #+#    #+#             */
/*   Updated: 2025/11/14 12:54:02 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*new_s;

	i = 0;
	new_s = (const unsigned char *)s;
	while (i < n)
	{
		if (new_s[i] == (unsigned char)c)
			return ((void *)&new_s[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int main() {
  char myStr[] = "Hello World!";
  char *myPtr = (char*)ft_memchr(myStr, 0, 0);
  if (myPtr != NULL) {
    printf("%s", myPtr);
  }
  return 0;
}
*/
