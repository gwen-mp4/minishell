/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:00:38 by storck            #+#    #+#             */
/*   Updated: 2025/11/12 16:51:39 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char	c;

	c = '0';
	printf("%d\n", isascii(c));
	printf("%d\n", ft_isascii(c));
	printf("%c", '\n');
	c = '1';
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = '9';
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = 'A';
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = 'Z';
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = 'a';
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = 'Z';
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = ' ';
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = '&';
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = 0;
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = 48;
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = 127;
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = 0x80;
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = 0xC8;
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');
	c = -1;
        printf("%d\n", isascii(c));
        printf("%d\n", ft_isascii(c));
        printf("%c", '\n');

	return (0);
}
*/
