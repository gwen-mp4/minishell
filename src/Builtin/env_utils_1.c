/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:00:38 by storck            #+#    #+#             */
/*   Updated: 2026/03/09 12:29:03 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_value(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_calloc(1, sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			ft_memmove(ret, &str[i], ft_strlen(str) - i);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*extract_key(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_calloc(1, sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=')
		{
			ft_memmove(ret, str, i);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int	append(t_list **list, char *elem)
{
	t_list	*new;

	if (!list_new_elem_str(&new, elem))
		return (0);
	if (!(*list))
	{
		(*list) = new;
		(*list)->next = *list;
		(*list)->prev = *list;
	}
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

int	free_list(t_list **list)
{
	t_list	*tmp;
	t_list	*current;

	if (!(*list))
		return (0);
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
	}
	free(current->str);
	free(current);
	*list = NULL;
	return (0);
}

int	init_envlst(t_data *data, char **env)
{
	int		i;
	char	*tmp;
	t_list	*list;

	if (!(*env))
		return (null_env(data));
	i = -1;
	list = NULL;
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (free_list(&list));
		if (!append(&list, tmp))
			return (free_list(&list));
	}
	data->envlst = list;
	printf("%s\n", data->envlst->str);
	return (1);
}
