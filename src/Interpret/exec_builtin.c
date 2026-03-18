/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:31:41 by storck            #+#    #+#             */
/*   Updated: 2026/03/18 12:04:57 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	no_path(char *str)
{
	if (!ft_strncmp(str, "./", 2))
	{
		error_permission_denied(str);
		exit (126);
	}
	else if (ft_strchr(str, '/'))
	{
		error_no_such_file(str);
		exit (127);
	}
	else
	{
		error_command_not_found(str);
		exit (127);
	}
}

void	exec_cmd(t_cmd *cmd, char **env)
{
	char	*path;

	if (!cmd || !cmd->av || !cmd->av[0])
		exit (0);
	set_fds(cmd);
	path = get_path(cmd->av[0], env);
	if (!path)
		no_path(cmd->av[0]);
	if (execve(path, cmd->av, env) == -1)
	{
		if (opendir(cmd->av[0]))
		{
			error_is_a_directory(cmd->av[0]);
			exit (126);
		}
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
		data->exit_code = exec_echo(arg + 1, data);
	else if (strncmp(arg[0], "cd", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_cd(data, cmd->av);
	else if (strncmp(arg[0], "pwd", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_pwd(cmd->av);
	else if (strncmp(arg[0], "export", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_export(arg, &(data->envlst), data);
	else if (strncmp(arg[0], "unset", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_unset(arg + 1, &data->envlst);
	else if (strncmp(arg[0], "env", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_env(data->envlst);
	else if (strncmp(arg[0], "exit", ft_strlen(arg[0])) == 0)
		exec_exit(arg, data);
}
