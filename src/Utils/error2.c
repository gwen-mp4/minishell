/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 12:12:46 by storck            #+#    #+#             */
/*   Updated: 2026/03/06 13:14:59 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_too_many_arguments(const char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	//data->exit_code = 1;
}

void	error_is_a_directory(const char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
}
