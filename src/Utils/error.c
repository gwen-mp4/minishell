/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:43:38 by storck            #+#    #+#             */
/*   Updated: 2026/02/20 15:01:29 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    error_cleanup_lexing(t_token *tokens, int status)
{
    if (status == 1)
        return (printf("syntax error near unexpected token '|'\n"), 2);
    clean_tokens(tokens);
    if (status == 0)
        printf("syntax error: unexpected EOF while looking for matching quote\n");
    return (2); //exit_code 2
}

int    error_cleanup_parsing(t_cmd *cmds, const char *error)
{
    free_cmds(cmds);
    if (error)
        printf("syntax error near unexpected token '%s'\n", error);
    return (2);
}
