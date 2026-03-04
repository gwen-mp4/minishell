/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:36:22 by gwen              #+#    #+#             */
/*   Updated: 2025/11/07 13:36:23 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			true_char;

	i = ft_strlen(s);
	true_char = (char)c;
	while (s[i] != true_char)
	{
		if (s[i] != true_char && i == 0)
			return (NULL);
		i--;
	}
	return ((char *)&s[i]);
}
/*
#include <stdio.h>
#include <string.h>
 
#define SIZE 40
 
int main(void)
{
  char buffer1[SIZE] = "computer program";
  char * ptr;
  int    ch = 'p';
 
  ptr = ft_strrchr( buffer1, ch );
  printf( "The last occurrence of %c in '%s' is '%s'\n",
            ch, buffer1, ptr );
 
}
*/
