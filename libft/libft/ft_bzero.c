/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:10:51 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 14:37:15 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
#include <stdio.h>
#include <string.h>

int     main(void)
{
        char str[50] = "/!\\ gogo test /!\\";
        printf("\nBefore memset(): %s\n", str);

        ft_bzero(str + 4, 4*sizeof(char));

        printf("After memset():  %s\n", str);
	printf("After memset():  %s\n", str + 8);
        return 0;
}
*/
