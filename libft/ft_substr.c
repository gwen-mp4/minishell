/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:15:18 by gwen              #+#    #+#             */
/*   Updated: 2025/11/08 15:15:20 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	s1_len;
	size_t			sub_len;

	s1_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > s1_len)
		return (ft_strdup(""));
	sub_len = s1_len - start;
	if (len > sub_len)
		len = sub_len;
	substr = ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, (char *)&s[start], len + 1);
	return (substr);
}
/*
#include <stdio.h>

int	main(void)
{
	const char	*str = "Hello world!";
	char	*sub;

	sub = ft_substr(str, 6, 5);
	printf("%s\n", sub);
	free(sub);

	sub = ft_substr(str, 0, 5);
	printf("%s\n", sub);
	free(sub);

	sub = ft_substr(str, 6, 50);
	printf("%s\n", sub);
	free(sub);

	sub = ft_substr(str, 20, 5);
	printf("%s\n", sub);
	free(sub);

	sub = ft_substr(str, 5, 0);
	printf("%s\n", sub);
	free(sub);

	sub = ft_substr("", 0, 5);
	printf("%s\n", sub);
	free(sub);

	return (0);
}
*/
