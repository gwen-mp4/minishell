/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:41:02 by storck            #+#    #+#             */
/*   Updated: 2026/02/27 10:41:06 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exec_pwd(void)
{
    char    buffer[BUFFER_SIZE + 1];
    char    *buffer2;
    int     large_buffer;

    if (getcwd(buffer, BUFFER_SIZE) != NULL)
        printf("%s\n", buffer);
    else
    {
        large_buffer = 4096;
        buffer2 = malloc(sizeof(char) * (large_buffer + 1));
        if (getcwd(buffer2, large_buffer) != NULL)
            printf("%s\n", buffer2);
        else
            perror("getcwd: ");
        free (buffer2);
    }
}
