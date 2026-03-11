/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:31:23 by storck            #+#    #+#             */
/*   Updated: 2026/03/11 13:47:38 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_echo(char **arg, t_quote_type *quote, t_data *data)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	while (ft_strcmp(arg[i], "-n") == 0)
		i++;
	while (arg[i])
	{
		if (quote[i] != SINGLE && ft_strchr(arg[i], '$'))
				replace_var(&arg[i], data);
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (ft_strcmp(arg[0], "-n") != 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
