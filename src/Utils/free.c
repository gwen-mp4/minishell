/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:32:03 by gwen              #+#    #+#             */
/*   Updated: 2026/03/06 13:25:05 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_tokens(t_token *tokens)
{
	t_token	*tmp;

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
		free(redir->filename);
		free(redir);
		redir = next;
	}
}

void	free_cmds(t_cmd *cmd)
{
	t_cmd	*next;
	int		i;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->av)
		{
			i = 0;
			while (cmd->av[i])
			{
				free(cmd->av[i]);
				i++;
			}
		}
		free(cmd->av);
		free(cmd->quote_type);
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
	free_list(&data->envlst);
	//free(data);
}
