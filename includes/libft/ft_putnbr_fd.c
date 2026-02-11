/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:41:42 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 13:29:09 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write (fd, "-2147483648", 11);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n >= 0)
	{
		if (n / 10 != 0)
			ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd((n % 10) + '0', fd);
	}
}
/*
int	main(void)
{
	ft_putnbr_fd(1648, 0);
	ft_putchar_fd('\n', 0);
	ft_putnbr_fd(123, 1);
        ft_putchar_fd('\n', 1);
	ft_putnbr_fd(-004, 2);
        ft_putchar_fd('\n', 2);
	ft_putnbr_fd(1648, 3);
        ft_putchar_fd('\n', 3);
}
*/
