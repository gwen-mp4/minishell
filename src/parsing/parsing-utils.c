/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:27:21 by storck            #+#    #+#             */
/*   Updated: 2026/02/12 11:27:23 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_last_start(char *str, int i)
{
	while (str[i] && str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13)
		&& str[i] != 34 && str[i] != 39)
		i--;
	return (i + 1);
}

int	increment_i(int i, char *str, char c)
{
	while (str[i] && str[i] != c)
		i++;
	return (i + 1);
}

int large_increment_i(int i, char *str)
{
	while (str[i] && str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13)
		&& str[i] != 34 && str[i] != 39)
		i++;
	return (i);
}

int increment_index(int i, char *str, char c)
{
    i++;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (0); //TODO manage error case: unclodsed " or '.
	else if (str[i + 1] == 32 || (str[i + 1] >= 9 && str[i + 1] <= 13))
	    i++;
    return (i);
}
