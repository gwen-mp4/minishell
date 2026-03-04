/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:39:07 by gwen              #+#    #+#             */
/*   Updated: 2026/03/04 14:42:44 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

// #include <string.h>
// #include <stdio.h>

// int	main(int ac, char **av)
// {
// 	(void) ac;
// 	printf("%d\n", ft_strcmp(av[1], av[2]));
// 	printf("%d\n", strcmp(av[1], av[2]));
// 	return (0);
// }