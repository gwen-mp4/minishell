/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:39:39 by storck            #+#    #+#             */
/*   Updated: 2026/03/04 16:34:34 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var   *init_var(char *name, char *content)
{
    t_var   *new;

    new = (t_var *)ft_calloc(1, sizeof(t_var));
    if (!new)
        return (NULL);
    new->name = name;
    new->content = content;
    
    new->next = NULL;
    return (new);
}

void    add_var(t_data *data, char *name, char *content)
{
    t_var   *new;
    t_var   *tmp;

    new = init_var(name, content);
    if (!data->vars)
    {
        data->vars = new;
        return ;
    }
    tmp = data->vars;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
