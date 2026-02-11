/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:01:45 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 14:41:58 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"
//#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}
/*
int	main(int argc, char **argv)
{
	char	n;
	char	o;

	n = 'N';
	o = 'O';
	//printf("%lu\n", strlen(argv[1]));
	//printf("%lu\n", ft_strlen(argv[1]));
	if (ft_strlen(argv[1]) == 5)
		write (1, &o, 1);
	else
		write (1, &n, 1);
	return (argc);
}
*/
