/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:21:40 by storck            #+#    #+#             */
/*   Updated: 2025/11/12 17:16:23 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
int	main(void)
{
	ft_putchar_fd('A', 0);
	ft_putchar_fd('\n', 0);
	ft_putchar_fd('B', 1);
        ft_putchar_fd('\n', 1);
	ft_putchar_fd('C', 2);
        ft_putchar_fd('\n', 2);
	ft_putchar_fd('D', 3);
        ft_putchar_fd('\n', 3);
	return (0);
}
*/
