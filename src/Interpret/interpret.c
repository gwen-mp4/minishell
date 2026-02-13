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

void    input_process(t_data *data, t_token *token)
{
    if (access(token->next->value, F_OK | R_OK))
    {
        data->infile = token->next->value;
        data->fd_in = file_read_process(token->next->value);
        token = token->next;
    }
    return ;
}

void    output_process(t_data *data, t_token *token)
{
    if (token->next->type == WORD)
    {
        data->outfile = token->next->value;
        data->fd_out = file_write_process(token->next->value);
        token = token->next;
    }
    return ;
}

void    append_process(t_data *data, t_token *token)
{
    if (token->next->type == WORD)
    {
        data->outfile = token->next->value;
        data->fd_out = open(data->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (data->fd_out == -1)
        {
            ft_putstr_fd("open ", 2);
            perror(token->next->value);
            return ;
        }
        token = token->next;
    }
    return ;
}

void    interpret(t_data *data)
{
    t_token *tmp;

    tmp = data->token;
    while (tmp)
    {
        if (tmp->type == PIPE)
            data->pipe_count++;
        else if (tmp->type == INPUT)
            input_process(data, tmp);
        else if (tmp->type == OUTPUT)
            output_process(data, tmp);
        else if (tmp->type == APPEND)
            append_process(data, tmp);
        else if (tmp->type == HEREDOC)
            printf("heredoc\n");
        else
            printf("word\n");
        tmp = tmp->next;
    }
}
