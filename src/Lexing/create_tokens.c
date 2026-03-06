/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:19:46 by storck            #+#    #+#             */
/*   Updated: 2026/03/06 13:10:42 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Function that will create a token, if value is WORD,*/
/*then duplicate it into token else NULL*/
t_token	*create_token(t_type type, char *value, t_quote_type quote)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (token->type == WORD && value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->quote_type = quote;
	token->next = NULL;
	return (token);
}

/*Adding the newly created token into the token list (**list)*/
void	add_back_token(t_token **list, t_token *new)
{
	t_token	*tmp;

	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
