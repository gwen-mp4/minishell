/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:31:41 by storck            #+#    #+#             */
/*   Updated: 2026/03/10 12:10:52 by marvin           ###   ########.fr       */
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
	if (strncmp(arg[0], "echo", ft_strlen(arg[0])) == 0)
		exec_echo(arg + 1);
	else if (strncmp(arg[0], "cd", ft_strlen(arg[0])) == 0)
		exec_cd(data, cmd->av);
	else if (strncmp(arg[0], "pwd", ft_strlen(arg[0])) == 0)
		exec_pwd();
	else if (strncmp(arg[0], "export", ft_strlen(arg[0])) == 0)
		exec_export(arg, &(data->envlst));
	else if (strncmp(arg[0], "unset", ft_strlen(arg[0])) == 0)
		exec_unset(arg + 1, &data->envlst);
	else if (strncmp(arg[0], "env", ft_strlen(arg[0])) == 0)
		exec_env(data->envlst);
	else if (strncmp(arg[0], "exit", ft_strlen(arg[0])) == 0)
		exec_exit(arg, data);
}
