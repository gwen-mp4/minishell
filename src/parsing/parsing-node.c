/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing-node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:19:46 by storck            #+#    #+#             */
/*   Updated: 2026/02/11 15:19:48 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node  *create_node(char *str, int len, t_node *list)
{
    t_node  *new;
    
    printf("entered node up to : %d\n", len);

    list->value = malloc(sizeof(char) * (len + 1));
    if (!list->value)
        return (NULL);
    ft_memcpy(list->value, str, len);
    list->value[len] = '\0';
    new = malloc(sizeof(t_node));
    if (!new)
        return (NULL);
    list->next = new;
    new->previous = list;
    list = list->next;
    return (list);
}
