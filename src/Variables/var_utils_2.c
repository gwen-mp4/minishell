/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:56:37 by storck            #+#    #+#             */
/*   Updated: 2026/03/16 10:25:53 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_eq_pos(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*return_content(char *rest, char *var, char *tmp_str, int len)
{
	char	*head;
	char	*str;
	char	*full_str;

	head = ft_strdup(tmp_str + len + 1);
	if (rest)
		str = ft_strjoin(head, rest);
	else
		str = ft_strdup(head);
	full_str = ft_strjoin(str, var + len);
	return (free(rest), free(head), free(str), full_str);
}

int	do_replace(char *cmd_str, t_quote_type type)
{
	char	*str;

	if (type == SINGLE)
		return (0);
	str = ft_strchr(cmd_str, '$');
	if (!str)
		return (0);
	if (str[1] == '\0')
		return (0);
	if (str[1] == ':')
		return (0);
	if (str[1] == ' ')
		return (0);
	if (str[1] == '=')
		return (0);
	return (1);
}
