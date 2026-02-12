/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:31:52 by gwen              #+#    #+#             */
/*   Updated: 2026/02/12 14:31:53 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Check special character and skip it*/
t_token	define_character(t_token *token, char *line, int i)
{
	if (line[i] == '|')
	{
		token->type = PIPE;
		i++;
	}
	else if (line[i] == '<')
	{
		token->type = INPUT;
		if (line[i + 1] == '<')
		{
			token->type = HEREDOC;
			i++;
		}
		i++;
	}
	else if (line[i] == '>')
	{
		token->type = OUTPUT;
		if (line[i + 1] == '>')
		{
			token->type = APPEND;
			i++;
		}
		i++;
	}
	else
		token->type = WORD;
}

/*Lexing the prompt, have to check quote too (to-do)*/
t_token	*lexer(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line && is_space(line[i]))
		i++;
	while (line && line[i])
	{
		define_character(data->token, line, line[i]);
	}
}
