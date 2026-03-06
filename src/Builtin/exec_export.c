/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:31:48 by storck            #+#    #+#             */
/*   Updated: 2026/03/06 12:56:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_export_msg(char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

void	export_list(t_data *data)
{
	t_env	*lst;
	size_t	i;

	lst = data->envlst;
	while (lst)
	{
		if (lst->value != NULL && (ft_strncmp(lst->key, "_", 1) != 0))
		{
			printf("declare -x %s=\"", lst->key);
			i = 0;
			while ((lst->value)[i])
			{
				if ((lst->value)[i] == '$' || (lst->value)[i] == '"')
					printf("\\%c", (lst->value)[i++]);
				else
					printf("%c", (lst->value)[i++]);
			}
			printf("\"\n");
		}
		else if (lst->value == NULL && (ft_strncmp(lst->key, "_", 1) != 0))
			printf("declare -x %s\n", lst->key);
		lst = lst->next;
	}
}

int	check_key(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	exec_export(char **args, t_data *data)
{
	int		i;
	int		status;
	char	*key;

	status = 0;
	i = 1;
	if (!args[1])
		return (export_list(data));
	while (args[i])
	{
		if (check_key(args[i]) == 0)
			status = error_export_msg(args[i]);
		else
		{
			key = extract_key(args[i]);
			if (env_entry_exists(key, data))
				update_envlst(key, extract_value(args[i]), data, false);
			else
				update_envlst(key, extract_value(args[i]), data, true);
		}
		i++;
	}
}
