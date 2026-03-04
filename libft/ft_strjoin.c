/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:15:33 by gwen              #+#    #+#             */
/*   Updated: 2025/11/08 15:15:34 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	j = 0;
	if (!s1 || !s2)
		return (NULL);
	dest = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
		dest[j++] = s1[i++];
	i = 0;
	while (s2[i])
		dest[j++] = s2[i++];
	dest[j] = '\0';
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str = "Hello ";
	char	*str2 = "world!";
	char	*joined;

	joined = ft_strjoin(str, str2);
	printf("%s\n", joined);
	free(joined);

	joined = ft_strjoin("", "world!");
	printf("%s\n", joined);
	free(joined);

	joined = ft_strjoin("Hello ", "");
	printf("%s\n", joined);
	free(joined);

	joined = ft_strjoin("", "");
	printf("%s\n", joined);
	free(joined);

	char	big[100] = "AAAAAAAAAAAAAAAAAAAAAAAA";
	char	big2[100] = "BBBBBBBBBBBBBBBBBBBBBBBB";

	joined = ft_strjoin(big, big2);
	printf("%s\n", joined);
	free(joined);

	if (!(joined = ft_strjoin(NULL, "world!")))
	printf("NULL\n");

	return (0);
}
	*/
