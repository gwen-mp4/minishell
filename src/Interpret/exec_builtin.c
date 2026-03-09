/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:31:41 by storck            #+#    #+#             */
/*   Updated: 2026/03/09 12:21:31 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *str)
{
	if (strncmp(str, "echo", ft_strlen(str)) == 0)
		return (1);
	else if (strncmp(str, "cd", ft_strlen(str)) == 0)
		return (1);
	else if (strncmp(str, "pwd", ft_strlen(str)) == 0)
		return (1);
	else if (strncmp(str, "export", ft_strlen(str)) == 0)
		return (1);
	else if (strncmp(str, "unset", ft_strlen(str)) == 0)
		return (1);
	else if (strncmp(str, "env", ft_strlen(str)) == 0)
		return (1);
	else if (strncmp(str, "exit", ft_strlen(str)) == 0)
		return (1);
	else
		return (0);
}

void	exec_builtin(t_cmd *cmd, char **arg, t_data *data)
{
	set_fds(cmd);
	if (strncmp(arg[0], "echo", ft_strlen(arg[0])) == 0)
	{
		printf("Entered echo\n");
		exec_echo(arg + 1);
	}
	else if (strncmp(arg[0], "cd", ft_strlen(arg[0])) == 0)
	{
		printf("Entered cd\n");
		exec_cd(data, cmd->av);
	}
	else if (strncmp(arg[0], "pwd", ft_strlen(arg[0])) == 0)
	{
		printf("Entered pwd\n");
		exec_pwd();
	}
	else if (strncmp(arg[0], "export", ft_strlen(arg[0])) == 0)
	{
		printf("Entered export\n");
		exec_export(arg, &(data->envlst));
	}
	else if (strncmp(arg[0], "unset", ft_strlen(arg[0])) == 0)
	{
		printf("Entered unset\n");
		exec_unset(arg, &(data->envlst));
	}
	else if (strncmp(arg[0], "env", ft_strlen(arg[0])) == 0)
	{
		printf("Entered env\n");
		exec_env(data->envlst);
	}
	else if (strncmp(arg[0], "exit", ft_strlen(arg[0])) == 0)
	{
		printf("Entered exit\n");
		exec_exit(arg, data);
	}
}
