/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:16:57 by gwen              #+#    #+#             */
/*   Updated: 2025/11/08 15:16:58 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*
void	upper_even(unsigned int i, char *c)
{
	if (i % 2 == 0 && *c >= 'a' && *c <= 'z')
		*c = *c - 32;
}

#include <stdio.h>

int	main(void)
{
	char	str[] = "abcdef";
	char	str2[] = "";

	printf("%s\n", str);
	ft_striteri(str, upper_even);
	printf("%s\n", str);

	ft_striteri(str2, upper_even);
	printf("%s\n", str2);

	ft_striteri(NULL, upper_even);

	return (0);
}
	*/