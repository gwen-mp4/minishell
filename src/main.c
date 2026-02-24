/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:54:48 by storck            #+#    #+#             */
/*   Updated: 2026/02/24 10:51:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Function to convert type into string for lexing test*/
const char	*token_type_str(t_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == INPUT)
		return ("<");
	if (type == HEREDOC)
		return ("<<");
	if (type == OUTPUT)
		return (">");
	if (type == APPEND)
		return (">>");
	if (type == PIPE)
		return ("PIPE");
	return ("UNKNOWN");
}

//Funcion to test the token list.
void	check_list(t_token *token)
{
	while (token)
	{
		printf("%s: %s\n", token_type_str(token->type), token->value);
		token = token->next;
	}
}

/*Function to test if parsing is good*/
void	check_cmd(t_cmd *cmd)
{
	int	i;
	int	j;
	t_redir	*redir;

	while (cmd)
	{
		printf("==CMD %p==\n", cmd);
		printf("Argv:\n");
		if (cmd->av)
		{
			i = 0;
			while (cmd->av[i])
			{
				printf("[%d] - %s\n", i, cmd->av[i]);
				i++;
			}
		}
		printf("Redirs:\n");
		redir = cmd->redirs;
		j = 0;
		while (redir)
		{
			printf("[%d] - %s  %s\n", j, token_type_str(redir->type), redir->filename);
			j++;
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void) ac;
	(void) av;
	(void) env;
	while (1)
	{
		setup_signal();
		//data.cmd = NULL;
		//init_data(&data, env);
		data.line = readline("$> ");
		if (!data.line)
			break ;
		if (*data.line)
			add_history(data.line);
		data.token = lexer(data.line);
		if (!data.token)
		{
			free(data.line);
			continue;
		}
		data.cmd = parsing(data.token);
		if (!data.cmd)
		{
			free(data.line);
			continue;
		}
		//check_list(data.token);
		check_cmd(data.cmd);
		//printf("%s\n", data.line);
		//interpret(&data);
		free(data.line);
		clean_tokens(data.token);
		free_cmds(data.cmd);
	}
	rl_clear_history();
	return (0);
}
