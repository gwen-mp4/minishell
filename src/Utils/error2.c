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
}

void	error_is_a_directory(const char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
}

void	error_invalid_identifier(const char *str)
{
	ft_putstr_fd("export: '", STDERR_FILENO);
	ft_putstr_fd((char *)str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	error_file_name_argument(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)str, STDERR_FILENO);
	ft_putstr_fd(": filename argument required\n", STDERR_FILENO);
}

void	free_exec(t_data *data, char **env, DIR *fd, char *str)
{
	closedir(fd);
	free_env(env, -1);
	if (ft_strchr(str, '/'))
	{
		error_is_a_directory(str);
		free_data(data);
		exit (126);
	}
	else
	{
		error_file_name_argument(str);
		free_data(data);
		exit(2);
	}
}
