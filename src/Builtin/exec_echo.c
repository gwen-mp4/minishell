/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:31:23 by storck            #+#    #+#             */
/*   Updated: 2026/03/19 13:17:27 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_option_n(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (ft_strncmp(str, "-n", 2))
		return (0);
	i = 2;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	exec_echo(char **arg, t_data *data)
{
	int	i;
	int	nline;

	(void) data;
	i = 0;
	nline = 1;
	if (!arg || !arg[0])
		return (ft_putchar_fd('\n', STDOUT_FILENO), 0);
	while (is_option_n(arg[i]))
	{
		nline = 0;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (nline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
