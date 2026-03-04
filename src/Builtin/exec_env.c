/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:29:29 by storck            #+#    #+#             */
/*   Updated: 2026/02/27 11:29:30 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    exec_env(t_data *data)
{
    t_env   *lst;

    lst = data->envlst;
    while (lst)
    {
        if (lst->value != NULL)
            printf("%s=%s\n", lst->key, lst->value);
        lst = lst->next;
    }
}
