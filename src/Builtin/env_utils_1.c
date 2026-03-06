/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:00:38 by storck            #+#    #+#             */
/*   Updated: 2026/03/06 14:58:04 by storck           ###   ########.fr       */
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

void	init_envlst(t_data *data)
{
	int		i;
	char	**enviro;
	char	*key;
	char	*value;

	i = 0;
	enviro = data->env;
	if (!enviro)
		return ;
	while (enviro[i])
	{
		key = extract_key(enviro[i]);
		value = extract_value(enviro[i]);
		update_envlst(key, value, data, true);
		printf("TEST [%d]: %s = %s\n", i, key, value);
		i++;
	}
}
