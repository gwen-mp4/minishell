/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:31:06 by gwen              #+#    #+#             */
/*   Updated: 2026/03/23 10:44:24 by storck           ###   ########.fr       */
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

static int	copy_cmd_arrays(t_cmd *cmd, char ***newav, int len)
{
	int	i;

	*newav = ft_calloc(len + 2, sizeof(char *));
	if (!*newav)
		return (0);
	i = 0;
	while (i < len)
	{
		(*newav)[i] = cmd->av[i];
		i++;
	}
	return (1);
}

int	add_arg_to_cmd(char *word, t_cmd *cmd)
{
	char			**newav;
	int				len;

	if (!word || !cmd)
		return (0);
	len = argv_len(cmd->av);
	if (!copy_cmd_arrays(cmd, &newav, len))
		return (0);
	newav[len] = ft_strdup(word);
	if (!newav[len])
		return (free(newav), 0);
	newav[len + 1] = NULL;
	free(cmd->av);
	cmd->av = newav;
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
