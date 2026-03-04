/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:15:48 by gwen              #+#    #+#             */
/*   Updated: 2025/11/08 15:15:50 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char *str)
{
	while (*str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	dest_len;
	size_t	s1_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1);
	s1_len = ft_strlen(s1);
	if (!s1_len || !set)
		return (ft_strdup(""));
	while (is_set(s1[i], (char *)set))
		i++;
	while (j > i && is_set(s1[j - 1], (char *)set))
		j--;
	dest_len = (s1_len - i) - (s1_len - j) + 1;
	if (dest_len < 1)
		return (ft_strdup(""));
	dest = ft_calloc(dest_len, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, (char *)&s1[i], dest_len);
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*str = "bababaabHello bab worldbabab!";
	char	*trimmed = ft_strtrim(str, "ab");

	printf("%s\n", trimmed);

	return (0);
}
*/
