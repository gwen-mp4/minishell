/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:19:41 by storck            #+#    #+#             */
/*   Updated: 2026/03/13 11:16:36 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char	*get_token_str(t_token *token)
{
	if (!token)
		return ("newline");
	if (token->type == WORD)
		return (token->value);
	if (token->type == PIPE)
		return ("|");
	if (token->type == INPUT)
		return ("<");
	if (token->type == OUTPUT)
		return (">");
	if (token->type == APPEND)
		return (">>");
	if (token->type == HEREDOC)
		return ("<<");
	return ("");
}

int	parsing_token_one(t_token **token, t_cmd **current, t_token *tokens_head,
		t_data *data)
{
	t_token		*tok;
	t_cmd		*cur;
	const char	*err;

	tok = *token;
	cur = *current;
	if (tok->type == WORD)
	{
		if (!add_arg_to_cmd(tok->value, tok->quote_type, cur))
			return (error_cleanup_parsing(*current, NULL, tokens_head, data),
				0);
	}
	else if (is_redir(tok->type))
	{
		if (!tok->next || tok->next->type != WORD)
		{
			err = get_token_str(tok->next);
			return (error_cleanup_parsing(*current, err, tokens_head, data), 0);
		}
		if (!add_redir_to_cmd(tok->type, tok->next->value, cur))
			return (error_cleanup_parsing(*current, NULL, tokens_head, data),
				0);
		*token = tok->next;
	}
	return (1);
}

int	parsing_token_two(t_token **token, t_cmd **current,
	t_token *tokens_head, t_data *data)
{
	t_token		*tok;
	t_cmd		*cur;
	const char	*err;

	tok = *token;
	cur = *current;
	if (tok->type == PIPE)
	{
		data->pipe_count++;
		if (!tok->next || tok->next->type == PIPE)
		{
			err = get_token_str(tok->next);
			error_cleanup_parsing(*current, err, tokens_head, data);
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
		return (error_cleanup_parsing(NULL, get_token_str(token), token, data),
			NULL);
	head = new_cmd();
	if (!head)
		return (NULL);
	tokens_head = token;
	current = head;
	while (token)
	{
		if (!parsing_token_one(&token, &current, tokens_head, data))
			return (NULL);
		if (!parsing_token_two(&token, &current, tokens_head, data))
			return (NULL);
		token = token->next;
	}
	return (head);
}
