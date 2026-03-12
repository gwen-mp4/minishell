/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:02:36 by storck            #+#    #+#             */
/*   Updated: 2026/03/12 11:34:44 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_declaration(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	new_var(t_data *data, char *str)
{
	char	*var_name;
	char	*var_content;
	int		i;

	var_name = malloc(sizeof(char));
	if (!var_name)
		return ;
	var_content = malloc(sizeof(char));
	if (!var_content)
		return ;
	i = var_declaration(str);
	memmove(var_name, str, i);
	memmove(var_content, &str[i + 1], ft_strlen(str) - (i));
	var_name[i] = 0;
	var_content[ft_strlen(str) - i] = 0;
	add_var(data, var_name, var_content);
}

void	pull_back_av(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		av[i - 1] = av[i];
		i++;
	}
	av[i - 1] = NULL;
	free(av[i]);
}

void	replace_var(char **var, t_data *data)
{
	char	*var_content;
	//int		len;

	if ((*var)[1] == '?')
		var_content = exit_code_to_str(data->exit_code, *var + 2);
	else
		var_content = get_var_content((*var) + 1, data);
	if (!var_content)
	{
		//free(*var);
		*var[0] = '\0';
		return ;
	}
	//len = ft_strlen(var_content);
	free (*var);
	*var = var_content;
}

void	filter_var(t_cmd *cmd, t_data *data)
{
	int		i;
	t_cmd	*tmp;

	if (!cmd->av || !cmd->av[0])
		return ;
	tmp = cmd;
	while (tmp && ft_strcmp(cmd->av[0], "export"))
	{
		i = 0;
		while (tmp->av[i])
		{
			if (var_declaration(tmp->av[i]) && i == 0)
			{
				if (!export_ex(tmp->av[i], &data->envlst))
					return (perror("malloc"));
				//new_var(data, tmp->av[i]);
				pull_back_av(tmp->av);
			}
			else if (tmp->quote_type[i] != SINGLE && ft_strchr(tmp->av[i], '$'))
				replace_var(&tmp->av[i], data);
			i++;
		}
		tmp = tmp->next;
	}
}
