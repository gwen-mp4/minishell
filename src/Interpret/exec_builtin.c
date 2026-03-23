/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:31:41 by storck            #+#    #+#             */
/*   Updated: 2026/03/23 17:14:15 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	path_is_set(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
			return (1);
		i++;
	}
	return (0);
}

void	no_path(char *str, char **env)
{
	if (access(str, F_OK) == 0 && !ft_strncmp(str, "./", 2))
	{
		error_permission_denied(str);
		free_env(env, -1);
		free(str);
		exit (126);
	}
	else if ((!path_is_set(env) && access(str, F_OK) == 0)
		|| ft_strchr(str, '/'))
	{
		error_no_such_file(str);
		free_env(env, -1);
		free(str);
		exit (127);
	}
	else
	{
		error_command_not_found(str);
		free_env(env, -1);
		free(str);
		exit (127);
	}
}

void	exec_cmd(t_cmd *cmd, char **env, t_data *data, pid_t *pids)
{
	char	*path;
	char	*name;
	DIR		*fd;

	if (!cmd || !cmd->av || !cmd->av[0])
		exit (0);
	name = ft_strdup(cmd->av[0]);
	path = get_path(cmd->av[0], env);
	if (!path)
	{
		free_find_way(data, pids, NULL);
		no_path(name, env);
	}
	free(name);
	if (execve(path, cmd->av, env) == -1)
	{
		fd = opendir(cmd->av[0]);
		if (fd)
		{
			free(path);
			free(pids);
			close_all(data->fd_in, data->fd_out);
			free_exec(data, env, fd, cmd->av[0]);
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
	if (ft_strncmp(arg[0], "echo", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_echo(arg + 1, data);
	else if (ft_strncmp(arg[0], "cd", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_cd(data, cmd->av);
	else if (ft_strncmp(arg[0], "pwd", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_pwd(cmd->av);
	else if (ft_strncmp(arg[0], "export", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_export(arg, &(data->envlst), data);
	else if (ft_strncmp(arg[0], "unset", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_unset(arg + 1, &data->envlst);
	else if (ft_strncmp(arg[0], "env", ft_strlen(arg[0])) == 0)
		data->exit_code = exec_env(data->envlst, arg);
	else if (ft_strncmp(arg[0], "exit", ft_strlen(arg[0])) == 0)
		exec_exit(arg, data);
}
