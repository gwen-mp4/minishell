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

void    set_fds(t_cmd *cmd)
{
    t_redir *tmp;

    tmp = cmd->redirs;
    while(tmp)
    {
        if (tmp->type == INPUT || tmp->type == HEREDOC)
            input_redirection(tmp);
        if (tmp->type == OUTPUT || tmp->type == APPEND)
            output_redirection(tmp);
        tmp = tmp->next;
    }
}

void    exec_cmd(t_cmd *cmd, char **env)
{
    char    *path;
    char    *tmp;

    set_fds(cmd);
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
    if(execve(path, cmd->av, env) == -1)
    {
        ft_putendl_fd("ERROR EXEC", 2);
        //total free minishell
        exit(1);
    }
    ft_putendl_fd("EXECUTED", 2);
}

void    do_pipe(t_cmd *cmd, char **env)
{
    pid_t   pid;
    int     p_fd[2];

    pipe_process(p_fd);
    pid = fork_process();
    if (!pid)
    {
        close(p_fd[0]);
        redirect_fd(p_fd[1], STDOUT_FILENO);
        exec_cmd(cmd, env);
        close(p_fd[1]);
    }
    else
    {
        close(p_fd[1]);
        redirect_fd(p_fd[0], STDIN_FILENO);
        waitpid(pid, NULL, 0);
        close(p_fd[0]);
    }
}

void    execution(t_cmd *cmd, t_data *data)
{
    pid_t   pid;

    if (data->pipe_count == 0)
    {
        pid = fork_process();
        if (!pid)
            exec_cmd(cmd, data->env);
        else   
            waitpid(pid, NULL, 0);
    }
    else
    {
        while (data->pipe_count >= 0)
        {
            do_pipe(cmd, data->env);
            data->pipe_count--;
            cmd = cmd->next;
        }
    }
    //ft_putendl_fd("do last cmd", 2);
    //exec_cmd(cmd, data->env);
    // while (cmd)
    // {
    //     printf("Boucle\n");
    //     pipe_process(p_fd);
    //     pid = fork_process();
    //     if (!pid)
    //     {
    //         printf("not a pid\n");
    //         exec_cmd(cmd, p_fd, data->env, data);
    //     }
    //     waitpid(pid, &status, 0);
    //     cmd = cmd->next;
    // }
}