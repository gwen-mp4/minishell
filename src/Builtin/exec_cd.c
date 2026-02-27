/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:02:03 by storck            #+#    #+#             */
/*   Updated: 2026/02/27 11:02:05 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exec_cd(char *path)
{
    char    *rel_path;

    if (opendir(path) != NULL)
    {
        if (chdir(path) == -1)
            perror ("chdir: ");
    }
    else
    {
        rel_path = malloc(sizeof(char) * 3);
        rel_path = "./\0";
        rel_path = ft_strjoin(rel_path, path);
        if (opendir(rel_path) != NULL)
        {
            if (chdir(rel_path) == -1)
                perror ("chdir: ");
        }
        free (rel_path);
    }
}
