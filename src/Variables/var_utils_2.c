/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:56:37 by storck            #+#    #+#             */
/*   Updated: 2026/03/17 12:57:58 by marvin           ###   ########.fr       */
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
	return (-1);
}

int	find_dollar(char *str)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !dq)
			sq = !sq;
		else if (str[i] == '"' && !sq)
			dq = !dq;
		else if (str[i] == '$' && !sq && is_expandable(str[i + 1]))
			return (i);
		i++;
	}
	return (-1);
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

/*Funtion (quote aware) that will return 1 if it's expandable*/
int	do_replace(char *cmd_str)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (*cmd_str)
	{
		if (*cmd_str == '\'' && !dq)
			sq = !sq;
		else if (*cmd_str == '"' && !sq)
			dq = !dq;
		else if (*cmd_str == '$' && !sq && is_expandable(*(cmd_str + 1)))
			return (1);
		cmd_str++;
	}
	return (0);
}

int	var_name_len(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (s[0] == '?')
		return (1);
	i = 0;
	while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
		i++;
	return (i);
}
