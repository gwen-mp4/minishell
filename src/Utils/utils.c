/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:08:54 by gwen              #+#    #+#             */
/*   Updated: 2026/03/05 13:59:38 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_redir(t_type type)
{
	if (type == INPUT || type == APPEND
		|| type == OUTPUT || type == HEREDOC)
		return (1);
	return (0);
}

int	is_number(char *num)
{
	int	n;

	n = ft_atoi(num);
	if (n != 0)
		return (1);
	else if (ft_isdigit(num[0]) && num[0] == '0')
		return (1);
	else
		return (0);
}
