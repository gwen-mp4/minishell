/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:31:48 by storck            #+#    #+#             */
/*   Updated: 2026/03/10 11:52:34 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	export_no_args(t_list *env)
{
	char	**arr;
	int		i;
	int		j;

	arr = lst_to_arr(env);
	if (!arr)
		return (false);
	sort_array(arr, len_list(env));
	i = 0;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			printf("%c", arr[i][j++]);
		if (arr[i][j] && arr[i][j] == '=')
			printf("=\"%s\"\n", &arr[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free(arr);
	return (true);
}

bool	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	exist(char *str, t_list *env)
{
	int		i;
	int		j;
	t_list	*tmp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	tmp = env;
	if (!ft_strncmp(tmp->str, str, i) && (tmp->str[i] == '\0'
		|| tmp->str[i] == '='))
		return (j);
	tmp = tmp->next;
	j++;
	while (tmp != env)
	{
		if (!ft_strncmp(tmp->str, str, i) && (tmp->str[i] = '\0'
			|| tmp->str[i] == '='))
			return (j);
		j++;
		tmp = tmp->next;
	}
	return (-1);
}

bool	export_ex(char *str, t_list **env)
{
	int		pos;
	int		i;
	char	*value;

	pos = exist(str, (*env));
	value = ft_strdup(str);
	if (!value)
		return (false);
	if (pos >= 0)
	{
		i = 0;
		while (i < pos)
		{
			*env = (*env)->next;
			i++;
		}
		free ((*env)->str);
		(*env)->str = value;
	}
	else if (pos == -1)
	{
		if (!append(env, value))
			return (false);
	}
	return (true);
}

int	exec_export(char **args, t_list **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	if (!args || !args[i])
	{
		printf("ICI\n");
		if (!env && !export_no_args(*env))
			perror("malloc");
		return (0);
	}
	while (args[i])
	{
		printf("NON, LA\n");
		if (!valid_identifier(args[i]))
		{
			ft_putendl_fd("export: invalid identifier", 2);
			exit_code = 1;
		}
		else if (!export_ex(args[i], env))
			return (perror("malloc"), 1);
		i++;
	}
	return (exit_code);
}
