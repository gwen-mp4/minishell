/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:26:24 by storck            #+#    #+#             */
/*   Updated: 2025/11/12 17:19:05 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
/*
int     main(void)
{
        ft_putstr_fd("Hello \n", 0);
        ft_putstr_fd("World!\n", 1);
        ft_putstr_fd("Fleur de lys\n", 2);
        ft_putstr_fd("Tabarnak!\n", 3);
        return (0);
}
*/
