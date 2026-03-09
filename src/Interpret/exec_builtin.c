/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:31:41 by storck            #+#    #+#             */
/*   Updated: 2026/03/09 18:51:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else
		return (0);
}

void	exec_builtin(t_cmd *cmd, char **arg, t_data *data)
{
	set_fds(cmd);
	if (ft_strcmp(arg[0], "echo") == 0)
		exec_echo(arg + 1);
	else if (ft_strcmp(arg[0], "cd") == 0)
		exec_cd(arg[0]);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(arg[0], "export") == 0)
		exec_export(arg, data);
	else if (ft_strcmp(arg[0], "unset") == 0)
		exec_unset(arg, data);
	else if (ft_strcmp(arg[0], "env") == 0)
		exec_env(data);
	else if (ft_strcmp(arg[0], "exit") == 0)
		exec_exit(arg, data);
}
