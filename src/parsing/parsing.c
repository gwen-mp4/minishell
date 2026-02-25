/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:19:41 by storck            #+#    #+#             */
/*   Updated: 2026/02/24 10:56:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parsing_token_one(t_token **token, t_cmd **current, t_token *tokens_head)
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
		{
			error_cleanup_parsing(*current, "newline");
			clean_tokens(tokens_head);
			return (0);
		}
		add_redir_to_cmd(tok->type, tok->next->value, cur);
		*token = tok->next;
	}
	return (1);
}

int	parsing_token_two(t_token **token, t_cmd **current,
	t_token *tokens_head, t_data *data)
{
	t_token	*tok;
	t_cmd	*cur;

	tok = *token;
	cur = *current;
	if (tok->type == PIPE)
	{
		data->pipe_count++;
		if (!tok->next || tok->next->type == PIPE)
		{
			error_cleanup_parsing(*current, "newline");
			clean_tokens(tokens_head);
			return (0);
		}
		(*current)->next = new_cmd();
		if (!cur->next)
			return (0);
		*current = cur->next;
	}
	return (1);
}

t_cmd	*parsing(t_token *token, t_data *data)
{
	t_cmd	*head;
	t_cmd	*current;
	t_token	*tokens_head;

	data->pipe_count = 0;
	if (!token)
		return (NULL);
	if (token->type == PIPE)
		return (error_cleanup_parsing(NULL, "|"),
			clean_tokens(token), NULL);
	head = new_cmd();
	if (!head)
		return (NULL);
	tokens_head = token;
	current = head;
	while (token)
	{
		if (!parsing_token_one(&token, &current, tokens_head))
			return (NULL);
		if (!parsing_token_two(&token, &current, tokens_head, data))
			return (NULL);
		token = token->next;
	}
	return (head);
}
