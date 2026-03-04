/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:16:44 by gwen              #+#    #+#             */
/*   Updated: 2025/11/08 15:16:46 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	unsigned int	i;

	if (!s)
		return (NULL);
	dest = ft_strdup(s);
	if (!dest)
		return (NULL);
	i = 0;
	while (dest[i])
	{
		dest[i] = (*f)(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
char	upper_even(unsigned int i, char c)
{
	if (i % 2 == 0 && c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

#include <stdio.h>

int	main(void)
{
	char	*str = "abcdef";
	char	*res;

	res = ft_strmapi(str, upper_even);
	printf("%s\n", res);
	free(res);

	res = ft_strmapi("", upper_even);
	printf("%s\n", res);
	free(res);

	res = ft_strmapi(NULL, upper_even);
	if (!res)
		printf("NULL\n");

	return (0);
}
	*/
