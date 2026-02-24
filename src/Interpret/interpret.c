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

void    set_fds(t_cmd *cmd, int p_fd[2])
{
    int     fd;
    t_redir *tmp;

    tmp = cmd->redirs;
    while (tmp)
    {
        printf("fd_loop\n");
        if (tmp->type == INPUT)
        {
            if (tmp->type == INPUT)
                fd = file_read_process(tmp->filename);
            else if (tmp->type == HEREDOC)
                fd = file_heredoc_process(tmp, tmp->filename);
            redirect_fd(fd, STDIN_FILENO);
            redirect_fd(p_fd[1], STDOUT_FILENO);
        }
        if (tmp->type == OUTPUT || tmp->type == APPEND)
        {
            if (tmp->type == OUTPUT)
                fd = file_write_process(tmp->filename);
            else if (tmp->type == APPEND)
                fd = file_append_process(tmp->filename);
            redirect_fd(p_fd[0], STDIN_FILENO);
            redirect_fd(fd, STDOUT_FILENO);
        }
        tmp = tmp->next;
    }
    close(p_fd[0]);
    close(p_fd[1]);
}

void    exec_cmd(t_cmd *cmd, int p_fd[2], char **env)
{
    char    *path;
    char    *tmp;

    set_fds(cmd, p_fd);
    tmp = cmd->av[0];
    path = get_path(cmd->av[0], env);
    if (!path)
    {
        ft_putendl_fd("ERROR PATH", 2);
        ft_putstr_fd(tmp, 2);
        ft_putendl_fd(": command not found", 2);
        //total free minishell
        exit(127);
    }
    // if(execve(path, cmd->av, env) == -1)
    // {
    //     ft_putendl_fd("ERROR EXEC", 2);
    //     //total free minishell
    //     exit(1);
    // }
    execve(path, cmd->av, env);
    ft_putendl_fd("EXECUTED", 2);
}

void    execution(t_cmd *cmd, t_data *data)
{
    pid_t   pid;
    int     p_fd[2];
    int     status;

    while (cmd)
    {
        int i = 0;
        while (cmd->av[i])
        {
            printf("%s\n", cmd->av[i]);
            i++;
        }
        pipe_process(p_fd);
        pid = fork_process();
        if (!pid)
            exec_cmd(cmd, p_fd, data->env);
        waitpid(pid, &status, 0);
        cmd = cmd->next;
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
