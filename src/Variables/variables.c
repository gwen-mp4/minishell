/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:02:36 by storck            #+#    #+#             */
/*   Updated: 2026/03/06 11:42:54 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int var_declaration(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (i);
        i++;
    }
    return (0);
}

void    new_var(t_data *data, char *str)
{
    char    *var_name;
    char    *var_content;
    int     i;

    var_name = malloc(sizeof(char));
    if (!var_name)
        return ;
    var_content = malloc(sizeof(char));
    if (!var_content)
        return ;
    i = var_declaration(str);
    memmove(var_name, str, i);
    memmove(var_content, &str[i + 1], ft_strlen(str) - (i));
    var_name[i] = 0;
    var_content[ft_strlen(str) - i] = 0;
    add_var(data, var_name, var_content);
}

void    pull_back_av(char **av)
{
    int i;

    i = 1;
    while (av[i])
    {
        av[i - 1] = av[i];
        i++;
    }
    av[i - 1] = NULL;
    free(av[i]);
}

void    replace_var(char *var, t_data *data)
{
    char    *var_content;
    int     len;

    var_content = get_var_content(var + 1, data);
    if (!var_content)
        return ;
    len = ft_strlen(var_content);
    memmove(var, var_content, len);
    var[len] = '\0';
}

void    filter_var(t_cmd *cmd, t_data *data)
{
    int     i;
    t_cmd   *tmp;

    tmp = cmd;
    while (tmp)
    {
        i = 0;
        while (tmp->av[i])
        {
            if (var_declaration(tmp->av[i]) && i == 0)
            {
                new_var(data, tmp->av[i]);
                pull_back_av(tmp->av);
            }
            else if (tmp->quote_type[i] != SINGLE && ft_strchr(tmp->av[i], '$'))
                replace_var(tmp->av[i], data);
            i++;
        }
        tmp = tmp->next;
    }
}
