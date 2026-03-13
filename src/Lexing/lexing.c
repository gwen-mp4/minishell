/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:31:52 by gwen              #+#    #+#             */
/*   Updated: 2026/03/13 11:06:46 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Check operator, create a token, add it to the chained list and skip it*/
int	handle_operator(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '|')
		add_back_token(tokens, create_token(PIPE, "|", NO_QUOTE));
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			add_back_token(tokens, create_token(HEREDOC, "<<", NO_QUOTE));
			(*i)++;
		}
		else
			add_back_token(tokens, create_token(INPUT, "<", NO_QUOTE));
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			add_back_token(tokens, create_token(APPEND, ">>", NO_QUOTE));
			(*i)++;
		}
		else
			add_back_token(tokens, create_token(OUTPUT, ">", NO_QUOTE));
	}
	(*i)++;
	return (*i);
}

int	handle_word(char *input, int *i, t_token **tokens, t_data *data)
{
	char			*word;
	t_quote_type	type;

	word = read_word(input, i, &type);
	if (!word)
		return (error_cleanup_lexing(*tokens, 0, data), -1);
	add_back_token(tokens, create_token(WORD, word, type));
	free(word);
	return (*i);
}

t_token	*lexer(char *input, t_data *data)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_operator(input[i]))
		{
			i = handle_operator(input, &i, &tokens);
			if (i == -1)
				return (NULL);
		}
		else
		{
			i = handle_word(input, &i, &tokens, data);
			if (i == -1)
				return (NULL);
		}
	}
	return (tokens);
}
