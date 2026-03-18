/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:32:05 by storck            #+#    #+#             */
/*   Updated: 2026/03/18 09:32:05 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value(char *str, t_data *data)
{
	char	*name;
	char	*value;
	int		len;

	len = var_name_len(str);
	if (len == 0)
		return (ft_strdup("$"));
	if (str[0] == '?')
		return (exit_code_to_str(data->exit_code, ""));
	name = ft_substr(str, 0, len);
	if (!name)
		return (NULL);
	value = get_var_content(name, data);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

static char	*build_result(char *head, char *value, char *tail)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(head, value);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, tail);
	free(tmp);
	return (res);
}

/*Function that will replace the variable*/
/*after $ by the actual value of the env*/
/*and concatenate all at the end (if no delimiter ofc)*/
void	replace_var(char **var, t_data *data)
{
	char	*value;
	char	*head;
	char	*res;
	int		pos;
	int		len;

	pos = find_dollar(*var);
	if (pos == -1)
		return ;
	head = ft_substr(*var, 0, pos);
	if (!head)
		return ;
	value = get_value((*var) + pos + 1, data);
	if (!value)
		return (free(head));
	len = var_name_len((*var) + pos + 1);
	res = build_result(head, value, (*var) + pos + 1 + len);
	free(head);
	free(value);
	if (!res)
		return ;
	free(*var);
	*var = res;
}

/*Function to remove a slot from the av if an av is null*/
void	remove_av_at(char **av, int i)
{
	free(av[i]);
	while (av[i + 1])
	{
		av[i] = av[i + 1];
		i++;
	}
	av[i] = NULL;
}
