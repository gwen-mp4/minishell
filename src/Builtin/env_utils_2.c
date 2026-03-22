/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:00:47 by storck            #+#    #+#             */
/*   Updated: 2026/03/19 14:27:03 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	list_new_elem_str(t_list **new, char *elem)
{
	(*new) = malloc(sizeof(t_list));
	if (*new == NULL)
		return (0);
	(*new)->str = elem;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

int	env_len(char **env)
{
	int	i;

	if (!env && !env[0])
		return (0);
	i = 0;
	while (env[i] && env[i][0] != '\0')
		i++;
	return (i);
}

void	free_env(char **env, int end)
{
	int	i;

	i = 0;
	if (end == -1)
		end = env_len(env);
	while (i < end)
	{
		free (env[i]);
		i++;
	}
	free (env);
}

char	**regen_env(t_list *envlst)
{
	int		i;
	int		len;
	char	**env;
	t_list	*tmp;

	tmp = envlst;
	len = len_list(envlst);
	env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		env[i] = ft_strdup(tmp->str);
		if (!env[i])
			return (free_env(env, i), NULL);
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

// bool	env_entry_exists(char *key, t_data *data)
// {
// 	t_env	*curr;

// 	curr = data->envlst;
// 	while (curr)
// 	{
// 		if (!strncmp(curr->key, key, ft_strlen(key)))
// 			return (true);
// 		curr = curr->next;
// 	}
// 	return (false);
// }

// t_env	*envlst_new(char *key, char *value)
// {
// 	t_env	*new;

// 	new = (t_env *)ft_calloc(1, sizeof(t_env));
// 	if (!new)
// 		return (NULL);
// 	// new->key = (char *)ft_calloc(1, sizeof(char));
// 	// if (!new->key)
// 	// 	return (NULL);
// 	// new->value = (char *)ft_calloc(1, sizeof(char));
// 	// if (!new->value)
// 	// 	return (NULL);
// 	//ft_memmove(new->key, key, ft_strlen(key));
// 	new->key = key;
// 	if (value)
// 		new->value = value;
// 		//ft_memmove(new->value, value, ft_strlen(value));
// 	else
// 		new->value = NULL;
// 	new->next = NULL;
// 	return (new);
// }

// void	envlst_back(t_env *new, t_data *data)
// {
// 	t_env	*curr;

// 	if (!data->envlst)
// 	{
// 		data->envlst = new;
// 		return ;
// 	}
// 	curr = data->envlst;
// 	while (curr && curr->next)
// 		curr = curr->next;
// 	curr->next = new;
// }

// void	update_envlst(char *key, char *value, t_data *data, bool create)
// {
// 	t_env	*envlst;

// 	envlst = data->envlst;
// 	while (envlst)
// 	{
// 		if (!ft_strcmp(key, envlst->key))
// 		{
// 			if (value)
// 				ft_memmove(envlst->value, value, ft_strlen(value));
// 			return ;
// 		}
// 		envlst = envlst->next;
// 	}
// 	if (create)
// 		envlst_back(envlst_new(key, value), data);
// }
