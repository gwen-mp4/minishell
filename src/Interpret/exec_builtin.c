/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:31:41 by storck            #+#    #+#             */
/*   Updated: 2026/03/13 14:15:43 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	if (!cmd || !cmd->av || !cmd->av[0])
		exit (0);
	signal_child();
	set_fds(cmd);
	path = get_path(cmd->av[0], env);
	if (!path && ft_strchr(cmd->av[0], '/'))
	{
		error_no_such_file(cmd->av[0]);
		exit (127);
	}
	if (!path)
	{
		error_command_not_found(cmd->av[0]);
		exit (127);
	}
	if (execve(path, cmd->av, env) == -1)
	{
		error_is_a_directory(cmd->av[0]);
		exit (1);
	}
}

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
		data->exit_code = exec_echo(arg + 1, cmd->quote_type + 1, data);
	else if (strncmp(arg[0], "cd", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_cd(data, cmd->av);
	else if (strncmp(arg[0], "pwd", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_pwd();
	else if (strncmp(arg[0], "export", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_export(arg, &(data->envlst));
	else if (strncmp(arg[0], "unset", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_unset(arg + 1, &data->envlst);
	else if (strncmp(arg[0], "env", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_env(data->envlst);
	else if (strncmp(arg[0], "exit", ft_strlen(arg[0])) == 0)
		exec_exit(arg, data);
}
