/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:32:03 by gwen              #+#    #+#             */
/*   Updated: 2026/02/19 10:32:04 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Only free *tokens and not **tokens because it's a chained list, so there's no malloc, otherwise it's segfault*/
void    clean_tokens(t_token *tokens)
{
    t_token *tmp;

    tmp = tokens;
    while (tmp)
    {
        tmp = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}

void	free_redir(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		free(redir);
		redir = next;
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		free(cmd->av);
		free_redir(cmd->redirs);
		free(cmd);
		cmd = next;
	}
}

void	free_data(t_data *data)
{
	free(data->line);
	free(data->infile);
	free(data->outfile);
	clean_tokens(data->token);
	free_cmds(data->cmd);
	free(data);
}
