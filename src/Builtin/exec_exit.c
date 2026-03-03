/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:32:23 by storck            #+#    #+#             */
/*   Updated: 2026/02/27 12:32:28 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



void    exec_exit(char **args)
{
    int status;

    //(get last exit status) status = ...;
    if (args[1])
    {
        if (args[2] && ft_isnumber(args[1]))
        {
            status = NULL;
            error_too_many_arguments(args[0]);
            //clean&exit_minishell();
            exit(exit_s);
        }
        else
            exit_s = ft_atoi(args[1]);
    }
    //clean&exit_minishell();
    exit(exit_s);
}
