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
		free_redirs(cmd->redirs);
		free(cmd);
		cmd = next;
	}
}

void	free_data(t_data *data)
{
	free(data->line);
	free(data->infile);
	free(data->outfile);
	error_cleanup(data->token);
	free_cmds(data->cmd);
	free(data);
}
