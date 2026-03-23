/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 11:44:41 by gwen              #+#    #+#             */
/*   Updated: 2026/03/23 12:08:53 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	word_count(const char *str)
{
	int	word;
	int	i;
	int	trigg;

	word = 0;
	i = 0;
	trigg = 0;
	while (str[i])
	{
		if (!is_ws(str[i]) && trigg == 0)
		{
			trigg = 1;
			word++;
		}
		else if (is_ws(str[i]))
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

static char	*write_word(const char *str)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && !is_ws(str[i]))
		i++;
	word = ft_calloc(i + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, str, i);
	word[i] = '\0';
	return (word);
}

static int	write_word2(const char *str, char **splitted)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_ws(str[i]))
		{
			splitted[j] = write_word(&str[i]);
			if (!splitted[j])
				return (free_all(j, splitted), 0);
			j++;
			while (str[i] && !is_ws(str[i]))
				i++;
		}
		else
			i++;
	}
	splitted[j] = NULL;
	return (1);
}

char	**ft_split_ws(char const *s)
{
	char	**dest;
	int		len;

	if (!s)
		return (NULL);
	len = word_count(s);
	dest = ft_calloc(len + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	if (!write_word2(s, dest))
		return (NULL);
	return (dest);
}
