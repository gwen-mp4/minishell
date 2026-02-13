/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:35:50 by storck            #+#    #+#             */
/*   Updated: 2025/11/12 17:29:04 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}
/*
#include <ctype.h>
#include <stdio.h>

int     main(void)
{
        char l = '[';
        char m = '[';
        char u = tolower(l);
        char x = ft_tolower(m);

        printf("%c in lowercase is %c\n", l, u);
        printf("%c in lowercase is %c\n", m, x);
        return (0);
}
*/
