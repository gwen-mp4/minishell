/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:19:41 by storck            #+#    #+#             */
/*   Updated: 2026/03/20 13:52:56 by gwen             ###   ########.fr       */
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

int	parsing_token_one(t_token **token, t_parse_h *h, t_data *data)
{
	t_token		*tok;
	const char	*err;

	tok = *token;
	if (tok->type == WORD)
	{
		if (!add_arg_to_cmd(tok->value, h->current))
			return (error_cleanup_parsing(h->head, NULL, h->tokens_head, data),
				0);
	}
	else if (is_redir(tok->type))
	{
		if (!tok->next || tok->next->type != WORD)
		{
			err = get_token_str(tok->next);
			return (error_cleanup_parsing(h->head, err, h->tokens_head, data),
				0);
		}
		if (!add_redir_to_cmd(tok->type, tok->next->value, h->current))
			return (error_cleanup_parsing(h->head, NULL, h->tokens_head, data),
				0);
		*token = tok->next;
	}
	return (1);
}

int	parsing_token_two(t_token **token, t_parse_h *h, t_data *data)
{
	t_token		*tok;
	const char	*err;

	tok = *token;
	if (tok->type == PIPE)
	{
		data->pipe_count++;
		if (!tok->next || tok->next->type == PIPE)
		{
			err = get_token_str(tok->next);
			error_cleanup_parsing(h->head, err, h->tokens_head, data);
			return (0);
		}
		h->current->next = new_cmd();
		if (!h->current->next)
			return (0);
		h->current = h->current->next;
	}
	return (1);
}

t_cmd	*parsing(t_token *token, t_data *data)
{
	t_parse_h	h;

	data->pipe_count = 0;
	if (!token)
		return (NULL);
	if (token->type == PIPE)
		return (error_cleanup_parsing(NULL, get_token_str(token), token, data),
			NULL);
	h.head = new_cmd();
	if (!h.head)
		return (NULL);
	h.tokens_head = token;
	h.current = h.head;
	while (token)
	{
		if (!parsing_token_one(&token, &h, data))
			return (NULL);
		if (!parsing_token_two(&token, &h, data))
			return (NULL);
		token = token->next;
	}
	return (h.head);
}
