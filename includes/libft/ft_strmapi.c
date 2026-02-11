/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:55:11 by storck            #+#    #+#             */
/*   Updated: 2025/11/12 17:25:27 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*mapi;

	i = 0;
	len = ft_strlen(s);
	mapi = malloc(sizeof(char) * (len + 1));
	if (!mapi)
		return (0);
	while (s[i])
	{
		mapi[i] = (*f)(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}
/*
char	test(unsigned int i, char c)
{
	c += i;
	return (c);
}

#include <stdio.h>

int	 main(int argc, char **argv)
{
	printf("%s\n", ft_strmapi(argv[1], test));
	return (argc);
}
*/
