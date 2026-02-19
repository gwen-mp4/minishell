/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:19:41 by storck            #+#    #+#             */
/*   Updated: 2026/02/19 10:31:44 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parsing(t_token *token)
{
	t_cmd	*head;
	t_cmd	*current;

	if (!token)
		return (NULL);
	if (token->type == PIPE)
		return (NULL);
	head = new_cmd();
	if (!head)
		return (NULL);
	current = head;
	while (token)
	{
		if (token->type == WORD)
			add_arg_to_cmd(token->value, current); //create the function to add argv to cmd
		else if (is_redir(token->type))
		{
			if (!token->next || token->next->type != WORD)
				return (NULL);
			add_redir_to_cmd(token->type, token->next->value, current); //create the function to add redirs to cmd
			token = token->next;
		}
		else if (token->type == PIPE)
		{
			if (!token->next || token->next->type == PIPE)
				return (NULL);
			current->next = new_cmd();
			if (!current->next)
				return (NULL);
			current = current->next;
		}
		token = token->next;
	}
	return (head);
}
