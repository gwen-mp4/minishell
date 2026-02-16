/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:13:58 by storck            #+#    #+#             */
/*   Updated: 2026/02/16 11:01:45 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    child(t_data *data, int p_fd[2], t_token *token)
{
    pid_t   pid;
    char    **args;

    args = get_args(token);
    pipe_process(p_fd);
    pid = fork_process();
    if (!pid)
    {
        close (p_fd[0]);
        if (data->fd_in == -1)
        {
            free_data(data);
            close(p_fd[1]);
            exit(EXIT_FAILURE);
        }
        redirect_fd(data->fd_in, STDIN_FILENO);
        redirect_fd(p_fd[1], STDOUT_FILENO);
        close(p_fd[0]);
        exec(data, args, data->env); //TODO : execution du pipe (s'inspirer de pipex mais adapter pour le fonctionnement en liste de tokens)
    }
    close(p_fd[1]);
}

void    parent(t_data *data, int p_fd[2], t_token *token)
{
    pid_t   pid;
    char    **args;

    args = get_args(token); //added token
    pid = fork_process();
    if (pid == 0)
    {
        close(p_fd[1]);
        redirect_fd(p_fd[0], STDIN_FILENO);
        if (data->fd_out == -1)
        {
            free_data(data);
            close(p_fd[0]);
            exit(EXIT_FAILURE);
        }
        redirect_fd(data->fd_out, STDOUT_FILENO);
        exec(data, args, data->env);
    }
    data->last_pid = pid;
    close(p_fd[0]);
    close(p_fd[1]);
}

int pipe_exec_process(t_data *data, t_token *token)
{
    int     p_fd[2];
    int     status;
    int     last_status;
    pid_t   finished_pid;
    t_token *tmp;

    tmp = token;
    child(data, p_fd, token);
    parent(data, p_fd, token);
    while (data->pipe_count > 0)
    {
        finished_pid = wait(&status);
        if (finished_pid == data->last_pid)
            last_status = status;
        data->pipe_count--;
    }
    if (WIFEXITED(last_status))
        return (WEXITSATUS(last_status));
    return (1);
}
