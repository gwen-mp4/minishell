/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:05:32 by storck            #+#    #+#             */
/*   Updated: 2026/02/13 12:05:44 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	path_count(const char *s, char c)
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

static void	ft_free_split(char **arr, int j)
{
	while (j-- > 0)
	{
		free(arr[j]);
	}
	free (arr);
}

static char	*path_add_w(const char *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 2));
	if (!word)
		return (NULL);
	ft_memcpy(word, s, i);
	word[i] = '/';
	word[i + 1] = '\0';
	return (word);
}

static int	path_populate(char **split, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			split[j] = path_add_w(&s[i], c);
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

char	**path_split(const char *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (path_count(s, c) + 1));
	if (!split)
		return (NULL);
	if (!path_populate(split, s, c))
		return (NULL);
	return (split);
}
