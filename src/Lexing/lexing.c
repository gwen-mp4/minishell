/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:31:52 by gwen              #+#    #+#             */
/*   Updated: 2026/02/13 15:46:19 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Check operator, create a token, add it to the chained list and skip it*/
int handle_operator(char *input, int *i, t_token **tokens)
{
    if (input[*i] == '|')
        add_back_token(tokens, create_token(PIPE, "|"));
    else if (input[*i] == '<')
    {
        if (input[*i + 1] == '<')
        {
            add_back_token(tokens, create_token(HEREDOC, "<<"));
            (*i)++;
        }
        else
            add_back_token(tokens, create_token(INPUT, "<"));
    }
    else if (input[*i] == '>')
    {
        if (input[*i + 1] == '>')
        {
            add_back_token(tokens, create_token(APPEND, ">>"));
            (*i)++;
        }
        else
            add_back_token(tokens, create_token(OUTPUT, ">"));
    }
    (*i)++;
    return (*i);
}

int handle_word(char *input, int *i, t_token **tokens)
{
    char *word;
    
    word = read_word(input, i);
    if (!word)
        return (error_cleanup(*tokens), -1);
    add_back_token(tokens, create_token(WORD, word));
    free(word);
    return (*i);
}

t_token *lexer(char *input)
{
    t_token *tokens;
    int i;
    
	tokens = NULL;
	i = 0;
    while (input[i])
	{
        while (is_space(input[i]))
			i++;
        if (!input[i])
            break;
        if (is_operator(input[i]))
            i = handle_operator(input, &i, &tokens);
        else
            i = handle_word(input, &i, &tokens);
    }
    return (tokens);
}
