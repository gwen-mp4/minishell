/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:27:33 by storck            #+#    #+#             */
/*   Updated: 2025/11/10 15:35:14 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	char l = 'a';
	char m = 'b';
	char u = toupper(l);
	char x = ft_toupper(m);

	printf("%c in uppercase is %c\n", l, u);
	printf("%c in uppercase is %c\n", m, x);
	return (0);
}
*/
