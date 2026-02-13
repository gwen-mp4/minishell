/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:43:38 by storck            #+#    #+#             */
/*   Updated: 2026/02/13 13:53:57 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Only free *tokens and not **tokens because it's a chained list, so there's no malloc, otherwise it's segfault*/
void    error_cleanup(t_token *tokens)
{
    t_token *tmp;

    tmp = tokens;
    while (tmp)
    {
        tmp = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}
