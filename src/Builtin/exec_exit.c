/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:32:23 by storck            #+#    #+#             */
/*   Updated: 2026/03/06 12:10:14 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_exit(char **args, t_data *data)
{
	int	status;

	status = 0;
	status = data->exit_code;
	if (args[1])
	{
		if (args[2] && is_number(args[1]))
		{
			status = 1;
			error_too_many_arguments(args[0]);
			//clean&exit_minishell();
			exit(status);
		}
		else
		status = ft_atoi(args[1]);
	}
	while (status < 0)
		status = 256 + status;
	while (status > 255)
		status = status - 256;
	//clean&exit_minishell();
	exit(status);
}
