/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:31:23 by storck            #+#    #+#             */
/*   Updated: 2026/02/27 12:31:29 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exec_echo(char **arg)
{
    int i;

    if (ft_strncmp(arg[0], "-n", 2) == 0)
        i = 1;
    else
        i = 0;
    while (arg[i])
    {
        printf("[W:%d] = ", i);
        ft_putstr_fd(arg[i], STDOUT_FILENO);
        if (arg[i + 1] != NULL)
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    printf("exited loop\n");
    if (ft_strncmp(arg[0], "-n", 2) != 0)
        ft_putchar_fd('\n', STDOUT_FILENO);
    printf("Echo Done\n");
    return ;
}
