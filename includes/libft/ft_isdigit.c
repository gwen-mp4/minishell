/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:01:01 by storck            #+#    #+#             */
/*   Updated: 2025/11/12 16:51:28 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>
#include "libft.h"

int	ft_isdigit(int n)
{
	if (n >= 48 && n <= 57)
		return (2048);
	else
		return (0);
}
/*
int	main(int argc, char **argv)
{
	char	n;

	n = argv[1][0];
	printf("%d\n", isdigit(n));
	printf("%d\n", ft_isdigit(n));
	return (argc);
}
*/
