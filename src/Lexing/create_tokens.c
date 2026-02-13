/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:19:46 by storck            #+#    #+#             */
/*   Updated: 2026/02/13 13:47:24 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Function that will create a token, if value is WORD,*/
/*then duplicate it into token else NULL*/
t_token  *create_token(t_type type, char *value)
{
    t_token  *token;
    
    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    if (token->type == WORD && value)
        token->value = ft_strdup(value);
    else
        token->value = NULL;
    token->next = NULL;
    return (token);
}
/*Adding the newly created token into the token list (**list)*/
void    add_back_token(t_token **list, t_token *new)
{
    t_token *tmp;

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

// int    add_arg(char **arg_list, int index, int len, char *str)
// {
//     int i;

//     i = 0;
//     arg_list[index] = malloc(sizeof(char) * len);
//     if (!arg_list[index])
//         return (0);
//     while (i < len - 1)
//     {
//         arg_list[index][i] = str[i];
//         i++;
//     }
//     arg_list[index][i] = '\0';
//     return (index + 1);
// }

// char    **gen_arg_list(char **arg_list, char *str)
// {
//     int i;
//     int count;
//     int start;

//     i = 0;
//     count = 0;
//     start  = 0;
//     while (str[i] && str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13
//             && str[i] != 34 && str[i] != 39))
// 		i++;
//     count = add_arg(arg_list, count, i - start, &str[start]);
//     start = i;
//     while (str[i])
//     {
//         if (str[i] == 34 || str[i] == 39)
//         {
//             start = i + 1;
//             i = increment_i(i, str, str[i]);
//             count = add_arg(arg_list, count, i - start, &str[start]);
//         }
//         else if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
//             i++;
//         else
//         {
//             start = i;
//             i = large_increment_i(i, str);
//             count = add_arg(arg_list, count, i + 1 - start, &str[start]);
//         }
//     }
//     if (str[i - 1] != 32 && !(str[i - 1] >= 9 && str[i - 1] <= 13)
// 			&& str[i - 1] != 34 && str[i - 1] != 39)
//     {
//         start = get_last_start(str, i);
//         count = add_arg(arg_list, count, i + 1 - start, &str[start]);
//     }
//     count = add_arg(arg_list, count, 1, &str[start]);
// 	return (arg_list);
// }
