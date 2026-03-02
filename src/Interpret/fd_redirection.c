/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:31:45 by storck            #+#    #+#             */
/*   Updated: 2026/03/02 15:01:04 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int input_redirection(t_redir *redir)
{
    int fd;

    if (redir->type == INPUT)
        fd = file_read_process(redir->filename);
    else
        fd = file_heredoc_process(redir, redir->filename);
    redirect_fd(fd, STDIN_FILENO);
    return (fd);
}

int output_redirection(t_redir *redir)
{
    int fd;

    if (redir->type == OUTPUT)
        fd = file_write_process(redir->filename);
    else
        fd = file_append_process(redir->filename);
    redirect_fd(fd, STDOUT_FILENO);
    return (fd);
}
