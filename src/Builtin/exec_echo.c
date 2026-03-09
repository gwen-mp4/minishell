/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:31:23 by storck            #+#    #+#             */
/*   Updated: 2026/03/09 10:37:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_echo(char **arg)
{
	int	i;

	if (ft_strcmp(arg[0], "-n") == 0)
		i = 1;
	else
		i = 0;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (ft_strcmp(arg[0], "-n") != 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return ;
}
