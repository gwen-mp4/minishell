/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:39:39 by storck            #+#    #+#             */
/*   Updated: 2026/03/13 16:44:56 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*exit_code_to_str(int code, char *rest)
{
	int		i;
	int		len;
	char	*str;
	char	*res;

	if (code >= 100)
		len = 3;
	else if (code >= 10 && code < 100)
		len = 2;
	else
		len = 1;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = len - 1;
	while (i >= 0)
	{
		str[i] = (code % 10) + '0';
		code /= 10;
		i--;
	}
	str[len] = '\0';
	res = ft_strjoin(str, rest);
	free(str);
	return (res);
}

char	*scalp(char **var)
{
	char	*rest;
	int		i;

	rest = ft_strdup(ft_strchr(*var, '/'));
	if (!rest)
		return (NULL);
	i = 0;
	while ((*var)[i])
	{
		if ((*var)[i] == '/')
		{
			(*var)[i] = '\0';
			break ;
		}
		i++;
	}
	return (rest);
}

char	*get_var_content(char *var, t_data *data)
{
	int		len;
	t_list	*tmp;
	char	*str;
	char	*rest;
	char	*head;
	char	*full_str;

	rest = NULL;
	tmp = data->envlst->next;
	if (ft_strchr(var, '/'))
		rest = scalp(&var);
	while (tmp != data->envlst)
	{
		len = get_eq_pos(tmp->str);
		if (!ft_strncmp(tmp->str, var, len)
			&& tmp->str[len] == '=')
		{
			head = ft_strdup(tmp->str + len + 1);
			if (rest)
				str = ft_strjoin(head, rest);
			else
				str = ft_strdup(head);
			full_str = ft_strjoin(str, var + len);
			return (free(rest), free(head), free(str), full_str);
		}
		tmp = tmp->next;
	}
	free(rest);
	return (NULL);
}

t_var	*init_var(char *name, char *content)
{
	t_var	*new;

	new = (t_var *)ft_calloc(1, sizeof(t_var));
	if (!new)
		return (NULL);
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
}

void	add_var(t_data *data, char *name, char *content)
{
	t_var	*new;
	t_var	*tmp;

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
