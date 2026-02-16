/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:29:57 by storck            #+#    #+#             */
/*   Updated: 2026/02/16 11:45:58 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub_s;
	size_t			slen;

	i = 0;
	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	sub_s = malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (0);
	while (i < len && s[i + start])
	{
		sub_s[i] = s[i + start];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*sub;

	sub = ft_substr("Hello World!", 4, 0);
	printf("%s\n", sub);
	free(sub);
	return (0);
}
*/
