/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:32:53 by storck            #+#    #+#             */
/*   Updated: 2025/11/12 17:17:16 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
/*
int     main(void)
{
        ft_putendl_fd("Hello ", 0);
        ft_putendl_fd("World!", 1);
        ft_putendl_fd("Fleur de lys", 2);
        ft_putendl_fd("Tabarnak!", 3);
        return (0);
}
*/
