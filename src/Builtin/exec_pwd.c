/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:41:02 by storck            #+#    #+#             */
/*   Updated: 2026/03/13 12:06:22 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_pwd(char **arg)
{
	char	buffer[PATH_MAX];

	if (arg[1] && arg[1][0] == '-' && arg[1][1] != '\0')
	{
		ft_putstr_fd("Minishell: pwd: ", 2);
		write(2, arg[1], 2);
		ft_putendl_fd(": invalid option", 2);
		return (1);
	}
	if (getcwd(buffer, PATH_MAX))
	{
		ft_putendl_fd(buffer, 1);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
