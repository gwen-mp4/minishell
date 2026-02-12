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

#include "minishell.h"

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

int    add_arg(char **arg_list, int index, int len, char *str)
{
    int i;

    i = 0;
    arg_list[index] = malloc(sizeof(char) * len);
    if (!arg_list[index])
        return (NULL);
    while (i < len - 1)
    {
        arg_list[count][i] = str[i];
        i++;
    }
    arg_list[count][i] = '\0';
    return (index + 1);
}

char    **gen_arg_list(char **arg_list, int count_total, char *str)
{
    int i;
    int count;
    int start;

    i = 0;
    count = 0;
    start  = 0;
    while (str[i] && str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13
            && str[i] != 34 && str[i] != 39))
		i++;
    count = add_arg(arg_list, count, start - i, &str[start]);
    start = i;
    while (str[i])
    {
        if (str[i] == 34 && str[i] == 39)
        {
            start = i + 1;
            i = increment_i(str, str[i])
            count = add_arg(arg_list, count, start - i, &str[start]);
            start = i + 1;
        }
    }
	return (arg_list);
}
