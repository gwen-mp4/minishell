/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:19:41 by storck            #+#    #+#             */
/*   Updated: 2026/02/20 15:14:43 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing_token_one(t_token **token, t_cmd **current)
{
	t_token	*tok;
	t_cmd	*cur;

	tok = *token;
	cur = *current;
	if (tok->type == WORD)
		add_arg_to_cmd(tok->value, cur);
	else if (is_redir(tok->type))
	{
		if (!tok->next || tok->next->type != WORD)
			return (error_cleanup_parsing(*current, "newline"), 0);
		add_redir_to_cmd(tok->type, tok->next->value, cur);
		*token = tok->next;
	}
	return (1);
}

int	parsing_token_two(t_token **token, t_cmd **current)
{
	t_token	*tok;
	t_cmd	*cur;

	tok = *token;
	cur = *current;
	if (tok->type == PIPE)
	{
		if (!tok->next || tok->next->type == PIPE)
			return (0);
		(*current)->next = new_cmd();
		if (!cur->next)
			return (0);
		*current = cur->next;
	}
	return (1);
}

t_cmd	*parsing(t_token *token)
{
	t_cmd	*head;
	t_cmd	*current;

	if (!token)
		return (NULL);
	if (token->type == PIPE)
		return (error_cleanup_lexing(token, 1), NULL);
	head = new_cmd();
	if (!head)
		return (NULL);
	current = head;
	while (token)
	{
		if (!parsing_token_one(&token, &current))
			return (NULL);
		if (!parsing_token_two(&token, &current))
			return (NULL);
		token = token->next;
	}
	return (head);
}
