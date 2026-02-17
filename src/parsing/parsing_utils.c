//42 header

#include "../../includes/minishell.h"

static int	argv_len(char **argv)
{
	int	i;

	i = 0;
	if !(argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

int	add_arg_to_cmd(char *word, t_cmd *cmd)
{
	int	**new;
	int	i;
	int	len;

	len = argv_len(cmd->av);
	new = malloc((len + 2) * sizeof(char *));
	if (!new)
		return (0);
	i = 0;
	while (i < len)
	{
		new[i] = cmd->av[i];
		i++;
	}
	new[len] = word;
	new[len + 1] = NULL;
	free(cmd->av);
	cmd->av = new;
	return (1);
}

t_redir	*new_redir(t_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	if (type == INPUT)
		redir->type == INPUT;
	else if (type == APPEND)
		redir->type == APPEND;
	else if (type = OUTPUT)
		redir->type = OUTPUT;
	else if (type == HEREDOC)
		redir->type = HEREDOC;
	redir->filename = filename;
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
