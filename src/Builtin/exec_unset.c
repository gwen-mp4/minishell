/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:32:06 by storck            #+#    #+#             */
/*   Updated: 2026/03/04 11:56:23 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    unset_helper(char *key, t_data *data)
{
    t_env   *current;
    t_env   *prev;

    prev = NULL;
    current = data->envlst;
    while (current)
    {
        if (!ft_strncmp(key, current->key, ft_strlen(key)))
        {
            if (prev)
                prev->next = current->next;
            else
                data->envlst = current->next;
            free (current);
            return ;
        }
        prev = current;
        current = current->next;
    }
}

void    exec_unset(char **args, t_data *data)
{
    int     i;
    bool    err;
    char    *ptr;

    i = 1;
    if (!args[1])
        return ;
    err = false;
    while (args[i])
    {
        if (!check_key(args[i]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			err = true;
        }
        else
        {
            ptr = extract_key(args[i]);
            ft_lstadd_back(&(data->envlst), ft_lstnew(ptr));
            unset_helper(extract_key(args[i]), data);
        }
    }
}
