/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:31:41 by storck            #+#    #+#             */
/*   Updated: 2026/02/27 09:31:48 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_builtin(char *str)
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

void    exec_builtin(t_cmd *cmd, char **arg, t_data *data)
{
    set_fds(cmd);
    if (strncmp(arg[0], "echo", ft_strlen(arg[0])) == 0)
        exec_echo(arg + 1);
    else if (strncmp(arg[0], "cd", ft_strlen(arg[0])) == 0)
        exec_cd(arg[0]);
    else if (strncmp(arg[0], "pwd", ft_strlen(arg[0])) == 0)
        exec_pwd();
    else if (strncmp(arg[0], "export", ft_strlen(arg[0])) == 0)
        exec_export(arg, data);
    else if (strncmp(arg[0], "unset", ft_strlen(arg[0])) == 0)
        exec_unset(arg, data);
    else if (strncmp(arg[0], "env", ft_strlen(arg[0])) == 0)
        exec_env();
    else if (strncmp(arg[0], "exit", ft_strlen(arg[0])) == 0)
        exec_exit(arg);
}
