/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:59:41 by storck            #+#    #+#             */
/*   Updated: 2025/11/12 16:52:07 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| (c >= 48 && c <= 57))
		return (8);
	else
		return (0);
}
/*
int	main(int argc, char **argv)
{
	char	c;

	c = argv[1][0];
	printf("%d\n", isalnum(c));
	printf("%d\n", ft_isalnum(c));
	return (argc);
}
*/
