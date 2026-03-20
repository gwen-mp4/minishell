/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:41:02 by storck            #+#    #+#             */
/*   Updated: 2026/03/20 14:54:43 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_pwd(char **arg)
{
	char	buffer[PATH_MAX];

	if (arg[1] && arg[1][0] == '-' && arg[1][1] != '\0')
		return (error_invalid_option(arg[1][1]), 2);
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
