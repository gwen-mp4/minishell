/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:31:06 by gwen              #+#    #+#             */
/*   Updated: 2026/03/05 13:54:00 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	argv_len(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

static int	copy_cmd_arrays(t_cmd *cmd, char ***newav, t_quote_type **newqt,
	int len)
{
	int	i;

	*newav = calloc(len + 2, sizeof(char *));
	if (!*newav)
		return (0);
	*newqt = malloc((len + 2) * sizeof(t_quote_type));
	if (!*newqt)
		return (free(*newav), 0);
	i = 0;
	while (i < len)
	{
		(*newav)[i] = cmd->av[i];
		if (cmd->quote_type)
			(*newqt)[i] = cmd->quote_type[i];
		i++;
	}
	return (1);
}

int	add_arg_to_cmd(char *word, t_quote_type quote, t_cmd *cmd)
{
	char			**newav;
	t_quote_type	*newqt;
	int				len;

	len = argv_len(cmd->av);
	if (!copy_cmd_arrays(cmd, &newav, &newqt, len))
		return (0);
	newav[len] = ft_strdup(word);
	if (!newav[len])
	{
		free(newav);
		free(newqt);
		return (0);
	}
	newav[len + 1] = NULL;
	newqt[len] = quote;
	free(cmd->av);
	free(cmd->quote_type);
	cmd->av = newav;
	cmd->quote_type = newqt;
	return (1);
}

t_redir	*new_redir(t_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (type == INPUT)
		redir->type = INPUT;
	else if (type == APPEND)
		redir->type = APPEND;
	else if (type == OUTPUT)
		redir->type = OUTPUT;
	else if (type == HEREDOC)
		redir->type = HEREDOC;
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
		return (free(redir), NULL);
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

int	add_redir_to_cmd(t_type type, char *filename, t_cmd *cmd)
{
	t_redir	*new;
	t_redir	*tmp;

	new = new_redir(type, filename);
	if (!new)
		return (0);
	if (!cmd->redirs)
	{
		cmd->redirs = new;
		return (1);
	}
	tmp = cmd->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}
