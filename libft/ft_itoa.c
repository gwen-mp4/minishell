/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:24:34 by storck            #+#    #+#             */
/*   Updated: 2025/11/14 13:26:20 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_num_size(long int n)
{
	int	size;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*num;
	int		size;
	long	nb;

	nb = n;
	size = ft_num_size(nb);
	num = malloc(sizeof(char) * (size + 1));
	if (!num)
		return (0);
	num[size--] = '\0';
	if (nb == 0)
		num[0] = '0';
	if (nb < 0)
	{
		num[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		num[size--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (num);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_itoa(-2));
	return (0);
}
*/
