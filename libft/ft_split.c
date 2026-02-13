/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:18:11 by storck            #+#    #+#             */
/*   Updated: 2025/11/14 14:09:23 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
//#include <stdio.h>

int	ft_count(const char *s, char c)
{
	int	count;
	int	mode;

	count = 0;
	mode = 0;
	while (*s)
	{
		if (!mode && *s != c)
		{
			count++;
			mode = 1;
		}
		if (*s == c)
			mode = 0;
		s++;
	}
	return (count);
}

static char	*ft_add_w(const char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	ft_memcpy(word, s, i);
	word[i] = '\0';
	return (word);
}

static void	ft_free_split(char **arr, int j)
{
	while (j-- > 0)
	{
		free(arr[j]);
	}
	free (arr);
}

static int	ft_populate(char **split, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			split[j] = ft_add_w(&s[i], c);
			if (!split[j])
				return (ft_free_split(split, j), 0);
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	split[j] = NULL;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!split)
		return (NULL);
	if (!ft_populate(split, s, c))
		return (NULL);
	return (split);
}
/*
int	main(int argc, char **argv)
{
	char	**list;
	int	i;

	i = 0;
	list = ft_split("\0aa\0bbb", '\0');
	while (list[i])
	{
		printf("%s\n", list[i]);
		i++;
	}
	(void) argv;
	return (argc);
}
*/
