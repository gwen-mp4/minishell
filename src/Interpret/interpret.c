/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:43:54 by storck            #+#    #+#             */
/*   Updated: 2026/02/13 12:43:57 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    set_fds(t_type type, int p_fd[2])
{
    if (redirs->type == INPUT)
    {
        close(p_fd[0]);
        redirect_fd(redirs->filename, STDIN_FILENO);
        redirect_fd(p_fd[1], STDOUT_FILENO);
        close(p_fd[1]);
    }
    else if (redirs->type == OUTPUT || redirs->type == APPEND)
    {
        close(p_fd[1]);
        redirect_fd(p_fd[0], STDIN_FILENO);
        redirect_fd(redirs->filename, STDOUT_FILENO);
        close(p_fs[0]);
    }
}

void    exec_cmd(t_cmd cmd, int p_fd[2])
{
    char    *path;
    char    *tmp;

    set_fds(cmd->redirs, p_fd);
    tmp = cmd->args[0];
    path = get_path(cmd->args[0], g_minishell.env);
    if (!path)
    {
        ft_putstr_fd(tmp, 2);
        ft_putendl_fd(": command not found", 2);
        //total free minishell
        exit(127);
    }
    if(execve(path, cmd->args, g_minishell.env) == -1)
    {
        //total free minishell
        exit(1);
    }
    
}

void    execution(t_cmd *cmd)
{
    pid_t   pid;
    int     p_fd[2];
    int     status;

    pipe_process(p_fd);
    while (cmd)
    {
        pid = fork_process();
        if (!pid)
            exec_cmd(cmd, p_fd);
        waitpid(pid, &status, 0);
        cmd->next;
    }
}

// void    input_process(t_data *data, t_token *token)
// {
//     if (access(token->next->value, F_OK | R_OK))
//     {
//         data->infile = token->next->value;
//         data->fd_in = file_read_process(token->next->value);
//         token = token->next;
//     }
//     return ;
// }

// void    output_process(t_data *data, t_token *token)
// {
//     if (token->next->type == WORD)
//     {
//         data->outfile = token->next->value;
//         data->fd_out = file_write_process(token->next->value);
//         token = token->next;
//     }
//     return ;
// }

// void    append_process(t_data *data, t_token *token)
// {
//     if (token->next->type == WORD)
//     {
//         data->outfile = token->next->value;
//         data->fd_out = open(data->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
//         if (data->fd_out == -1)
//         {
//             ft_putstr_fd("open ", 2);
//             perror(token->next->value);
//             return ;
//         }
//         token = token->next;
//     }
//     return ;
// }

// void    interpret(t_data *data)
// {
//     t_token *tmp;

//     tmp = data->token;
//     while (tmp)
//     {
//         if (tmp->type == PIPE)
//             data->pipe_count++;
//         else if (tmp->type == INPUT)
//             input_process(data, tmp);
//         else if (tmp->type == OUTPUT)
//             output_process(data, tmp);
//         else if (tmp->type == APPEND)
//             append_process(data, tmp);
//         else if (tmp->type == HEREDOC)
//             printf("heredoc\n");
//         else
//             printf("word\n");
//         tmp = tmp->next;
//     }
// }
