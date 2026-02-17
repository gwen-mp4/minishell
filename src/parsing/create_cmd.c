//42 header

#include "../../includes/minishell.h"

/*Function to create a new command*/
t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->av = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}
