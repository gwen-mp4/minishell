/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:01:23 by storck            #+#    #+#             */
/*   Updated: 2025/11/12 16:51:15 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	else
		return (0);
}
/*
int	main(int argc, char **argv)
{
	char	c;

	c = argv[1][0];
	printf("%d\n", isprint(c));
	printf("%d\n", ft_isprint(c));

	c = 31;
        printf("%d\n", isprint(c));
        printf("%d\n", ft_isprint(c));

	c = 127;
        printf("%d\n", isprint(c));
        printf("%d\n", ft_isprint(c));

	return (argc);
}
*/
