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
        data->fd_in = open(token->next->value, O_RDONLY, 0644);
        if (data->fd_in == -1)
        {
            ft_putstr_fd("open ", 2);
            perror(token->next->value);
            return ;
        }
        token = token->next;
    }
    return ;
}

void    output_process(t_data *data, t_token *token)
{
    if (token->next->type == WORD)
    {
        data->outfile = token->next->value;
        data->fd_out = open(data->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
        switch (tmp->type)
        {
            //case (PIPE):
                //pipe_process();
            case (INPUT):
                input_process(data, tmp);
            case (OUTPUT):
                output_process(data, tmp);
            case (APPEND):
                append_process(data, tmp);
            //case (HEREDOC):
                //heredoc_process();
            default:
                //word_process();
                printf("default\n");
        }
        tmp = tmp->next;
    }
}
