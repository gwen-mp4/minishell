/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:15:59 by gwen              #+#    #+#             */
/*   Updated: 2025/11/08 15:16:00 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *str, char sep)
{
	int	word;
	int	i;
	int	trigg;

	word = 0;
	i = 0;
	trigg = 0;
	while (str[i])
	{
		if (str[i] != sep && trigg == 0)
		{
			trigg = 1;
			word++;
		}
		else if (str[i] == sep)
			trigg = 0;
		i++;
	}
	return (word);
}

static void	free_all(int n, char **strs)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	*write_word(const char *str, char sep)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	word = ft_calloc(i + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, str, i);
	word[i] = '\0';
	return (word);
}

static int	write_word2(const char *str, char sep, char **splitted)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != sep)
		{
			splitted[j] = write_word(&str[i], sep);
			if (!splitted[j])
				return (free_all(j, splitted), 0);
			j++;
			while (str[i] && str[i] != sep)
				i++;
		}
		else
			i++;
	}
	splitted[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		len;

	if (!s)
		return (NULL);
	len = word_count(s, c);
	dest = ft_calloc(len + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	if (!write_word2(s, c, dest))
		return (NULL);
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	**res;
	int		i;

	res = ft_split("222    2      Hello   world    2  ", '2');
	printf("Test1\n");
	for (i = 0; res[i]; i++)
		printf("[%d] %s\n\n", i, res[i]);
	for (i = 0; res[i]; i++)
		free(res[i]);
	free(res);

	return (0);
}
*/
