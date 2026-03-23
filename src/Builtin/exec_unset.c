/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:32:06 by storck            #+#    #+#             */
/*   Updated: 2026/03/23 17:08:41 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	syntax(char *str)
{
	int	i;

	if (!is_special_op(str[0]))
		return (false);
	i = 0;
	while (str[i])
	{
		if (!is_special_op(str[i]) && str[i] != '-')
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
	while (str[i])
		i++;
	j = 0;
	tmp = env;
	if (!ft_strncmp(tmp->str, str, i))
		return (j);
	tmp = tmp->next;
	j++;
	while (tmp != env)
	{
		if (!ft_strncmp(tmp->str, str, i))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

static void	check_env(t_list *tmp, t_list **env)
{
	if (tmp == *env)
		*env = tmp->next;
	if (tmp->next == tmp)
		*env = NULL;
}

bool	unset(char *str, t_list **env)
{
	int		pos;
	int		i;
	t_list	*tmp;

	if (!str || !*str)
		return (false);
	if (!syntax(str))
		return (false);
	pos = exist(str, *env);
	if (pos == -1)
		return (false);
	tmp = (*env);
	i = 0;
	while (i++ < pos)
		tmp = tmp->next;
	free(tmp->str);
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	check_env(tmp, env);
	free(tmp);
	tmp = NULL;
	return (false);
}

int	exec_unset(char **args, t_list **env)
{
	int	exit_code;
	int	i;

	exit_code = 0;
	i = 0;
	if (args[0] && args[0][0] == '-' && args[0][1] != '\0')
	{
		error_invalid_option(args[0][1]);
		return (2);
	}
	while (args[i])
	{
		if (unset(args[i], env))
		{
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd(" :command not found", STDERR_FILENO);
			exit_code = 1;
		}
		i++;
	}
	return (exit_code);
}
