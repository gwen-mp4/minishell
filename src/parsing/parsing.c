/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:19:41 by storck            #+#    #+#             */
/*   Updated: 2026/02/11 14:11:28 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*simplify_spaces(char *str, int start)
{
	int	i;

	i = start + 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	ft_memmove(&str[start + 1], &str[i], ft_strlen(str) - (i - 1));
	return (str);
}

char	*clean_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && str[i] == str[i + 1])
			ft_memmove(&str[i], &str[i + 2], ft_strlen(str) - (i + 1));
		else
			i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			str = simplify_spaces(str, i);
		i++;
	}
	return (str);
}

int	counting(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			count++;
		if (str[i] == 34 || str[i] == 39)
		{
			if (i > 0 && (count == 0 || (str[i + 1] != 32
				&& !(str[i - 1] >= 9 && str[i - 1] <= 13))))
				count++;
			if (i == 0)
				count++;
			i = increment_index(i, str, str[i]);
		}
		i++;
	}
	if (str[i - 1] != 32 && !(str[i - 1] >= 9 && str[i - 1] <= 13)
			&& str[i - 1] != 34 && str[i - 1] != 39)
		count++;
	return (count);
}

char	*parsing(char *cmd)
{
	char	*tmp;
	char	**arg_list;
	int		node_count;
	//t_node	list;

	tmp = ft_strdup(cmd);
	tmp = clean_str(tmp);
	node_count = counting(tmp); // Subject to change in case of commands with arguments, ex: "cat -e"
	arg_list = malloc(sizeof(char *) * node_count + 1);
	if (!arg_list)
		return (NULL);
	arg_list = gen_arg_list(arg_list, node_count, tmp);
	//list = *gen_list(tmp);
	//printf("exited\n");
	//int	i = 0;
	//while (i < node_count)
	//{
	//	printf("%s\n", list.value);
	//	list = *list.next;
	//	i++;
	//}
	printf("%d\n", node_count);
	return (tmp);
}
