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

#include "../minishell.h"

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
	char	c;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39))
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == '\0')
				return (0); //TODO manage error case: unclodsed " or '.
			count++;
		}
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			count++;
		i++;
	}
	return (count);
}

t_node	*gen_list(char *str)
{
	int		start;
	int		i;
	char	c;
	t_node	*list;
	t_node	*tmp;

	start = 0;
	i = 0;
	list = malloc(sizeof(t_node));
	if (!list)
		return (NULL);
	tmp = list;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39))
		{
			if (start != i)
			{
				list = create_node(&str[start], i, list);
				start = i + 1;
			}
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
			list = create_node(&str[start], i - 1, list);
			start = i + 1;
		}
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		{
			if (start != i)
			{
				list = create_node(&str[start], i - 1, list);
				start = i + 1;
			}
			while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
				i++;
			list = create_node(&str[start], i - 1, list);
			start = i + 1;
		}
		//printf("[%d] So far so good.\n", i);
		i++;
	}
	list = list->previous;
	free(list->next);
	return (list);
}

char	*parsing(char *cmd)
{
	char	*tmp;
	int		node_count;
	t_node	list;

	tmp = ft_strdup(cmd);
	tmp = clean_str(tmp);
	node_count = counting(tmp); // Subject to change in case of commands with arguments, ex: "cat -e"
	list = *gen_list(tmp);
	printf("exited\n");
	int	i = 0;
	while (i < node_count)
	{
		printf("%s\n", list.value);
		list = *list.next;
		i++;
	}
	printf("%d\n", node_count);
	return (tmp);
}
