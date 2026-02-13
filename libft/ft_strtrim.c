/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:18:49 by storck            #+#    #+#             */
/*   Updated: 2025/11/13 15:08:07 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_isinset(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_s_trim_len(const char *s1, const char *set)
{
	int	i;
	int	trim;

	trim = 0;
	i = 0;
	while (s1[i])
	{
		if (ft_isinset(set, s1[i]))
			trim++;
		else
			break ;
		i++;
	}
	return (trim);
}

int	ft_e_trim_len(const char *s1, const char *set)
{
	int	len;
	int	trim;

	trim = 0;
	len = ft_strlen(s1) - 1;
	while (len >= 0)
	{
		if (ft_isinset(set, s1[len]))
			trim++;
		else
			break ;
		len--;
	}
	return (trim);
}

char	*ft_zerotrim(void)
{
	char	*trim;

	trim = malloc(sizeof(char));
	if (!trim)
		return (0);
	trim[0] = '\0';
	return (trim);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		s_trim;
	int		e_trim;
	int		i;
	int		len;
	char	*trim;

	i = 0;
	s_trim = ft_s_trim_len(s1, set);
	if (s_trim == (int)ft_strlen(s1))
		return (ft_zerotrim());
	e_trim = ft_e_trim_len(s1, set);
	len = (ft_strlen(s1) + 1) - s_trim - e_trim;
	trim = malloc(sizeof(char) * len);
	if (!trim)
		return (0);
	while (i < len - 1)
	{
		trim[i] = s1[i + s_trim];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	printf("%s\n", ft_strtrim(argv[1], argv[2]));
	return (argc);
}
*/
