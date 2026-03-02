/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:33:27 by gwen              #+#    #+#             */
/*   Updated: 2026/03/02 11:49:31 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// /*Function to convert type into string for lexing test*/
// const char	*token_type_str(t_type type)
// {
// 	if (type == WORD)
// 		return ("WORD");
// 	if (type == INPUT)
// 		return ("<");
// 	if (type == HEREDOC)
// 		return ("<<");
// 	if (type == OUTPUT)
// 		return (">");
// 	if (type == APPEND)
// 		return (">>");
// 	if (type == PIPE)
// 		return ("PIPE");
// 	return ("UNKNOWN");
// }

// //Funcion to test the token list.
// void	check_list(t_token *token)
// {
// 	while (token)
// 	{
// 		printf("%s: %s\n", token_type_str(token->type), token->value);
// 		token = token->next;
// 	}
// }

// /*Function to test if parsing is good*/
// void	check_cmd(t_cmd *cmd)
// {
// 	int	i;
// 	int	j;
// 	t_redir	*redir;

// 	while (cmd)
// 	{
// 		printf("==CMD %p==\n", cmd);
// 		printf("Argv:\n");
// 		if (cmd->av)
// 		{
// 			i = 0;
// 			while (cmd->av[i])
// 			{
// 				printf("[%d] - %s\n", i, cmd->av[i]);
// 				i++;
// 			}
// 		}
// 		printf("Redirs:\n");
// 		redir = cmd->redirs;
// 		j = 0;
// 		while (redir)
// 		{
// 			printf("[%d] - %s  %s\n", j, token_type_str(redir->type), redir->filename);
// 			j++;
// 			redir = redir->next;
// 		}
// 		cmd = cmd->next;
// 	}
// }
