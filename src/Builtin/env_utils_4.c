/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 10:42:07 by gwen              #+#    #+#             */
/*   Updated: 2026/03/23 14:25:35 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_shlvl(t_data *data)
{
	t_list	*current;
	char	*val;
	char	*new_str;

	current = data->envlst;
	while (current)
	{
		if (!ft_strncmp(current->str, "SHLVL=", 6))
		{
			val = ft_itoa(ft_atoi(current->str + 6) + 1);
			if (!val)
				return (0);
			new_str = ft_strjoin("SHLVL=", val);
			free(val);
			if (!new_str)
				return (0);
			free(current->str);
			current->str = new_str;
			return (1);
		}
		current = current->next;
	}
	return (append(&data->envlst, ft_strdup("1")));
}

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
