/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:02:36 by storck            #+#    #+#             */
/*   Updated: 2026/03/23 12:32:22 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Function that will set the export OR replace*/
/*the variable and removing the quotes*/
/*and remove null string in the case if*/
/*$DONTEXIST so that there're no problems*/
static void	process_cmd_args(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd->av[i])
	{
		if (var_declaration(cmd->av[i]) && i == 0)
		{
			if (!export_ex(cmd->av[i], &data->envlst))
				return (perror("malloc"));
			pull_back_av(cmd->av);
		}
		else
		{
			while (do_replace(cmd->av[i]))
				replace_var(&cmd->av[i], data);
			word_split(cmd, &i);
			strip_quotes(&cmd->av[i]);
			if (!cmd->av[i][0])
				remove_av_at(cmd->av, i);
			else
				i++;
		}
	}
}

/*Function that will do basically do the same*/
/*thing as above but except i starts at 1*/
/*because we don't take export as argument*/
static void	process_export_args(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 1;
	while (cmd->av[i])
	{
		while (do_replace(cmd->av[i]))
			replace_var(&cmd->av[i], data);
		if (!cmd->av[i][0])
			remove_av_at(cmd->av, i);
		else
			strip_quotes(&cmd->av[i++]);
	}
}

static void	process_redir_args(t_redir *redir, t_data *data)
{
	while (redir)
	{
		while (do_replace(redir->filename))
			replace_var(&redir->filename, data);
		strip_quotes(&redir->filename);
		redir = redir->next;
	}
}

/*Function that will check for anything to expand if export or not*/
void	filter_var(t_cmd *cmd, t_data *data)
{
	t_cmd	*tmp;

	if (!cmd || !cmd->av || !cmd->av[0])
	{
		if (cmd->redirs != NULL)
			process_redir_args(cmd->redirs, data);
		return ;
	}
	tmp = cmd;
	while (tmp && tmp->av && tmp->av[0])
	{
		if (ft_strcmp(tmp->av[0], "export") == 0)
			process_export_args(tmp, data);
		else
			process_cmd_args(tmp, data);
		if (tmp->redirs)
			process_redir_args(tmp->redirs, data);
		tmp = tmp->next;
	}
}
