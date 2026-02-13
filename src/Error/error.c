/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:43:38 by storck            #+#    #+#             */
/*   Updated: 2026/02/13 10:43:41 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    error_cleanup(t_token **tokens)
{
    t_token *tmp;

    tmp = *tokens;
    while (tmp)
    {
        if (tmp->value)
            free(tmp->value);
        tmp = tmp->next;
        free(tmp->prev);
    }
    free(tmp);
    free(tokens);
}
