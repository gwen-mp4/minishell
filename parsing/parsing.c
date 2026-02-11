/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:19:41 by storck            #+#    #+#             */
/*   Updated: 2026/02/11 14:11:28 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*simplify_spaces(char *str, int start)
{
	int	i;

	i = start + 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	ft_memmove(&str[start + 1], &str[i], ft_strlen(str) - (i - 1));
	return (str);
}

char	*clean_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && str[i] == str[i + 1])
			ft_memmove(&str[i], &str[i + 2], ft_strlen(str) - (i + 1));
		else
			i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			str = simplify_spaces(str, i);
		i++;
	}
	return (str);
}

char	*parsing(char *cmd)
{
	char	*tmp;

	tmp = ft_strdup(cmd);
	tmp = clean_str(tmp);
	return (tmp);
}
