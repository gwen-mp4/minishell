/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:29:29 by storck            #+#    #+#             */
/*   Updated: 2026/03/20 14:34:45 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_env(t_list	*env, char **av)
{
	t_list	*lst;

	if (av[1])
	{
		error_no_such_file(av[1]);
		return (127);
	}
	lst = env;
	if (ft_strchr(lst->str, '='))
		ft_putendl_fd(lst->str, 1);
	lst = lst->next;
	while (lst != env)
	{
		if (ft_strchr(lst->str, '='))
			ft_putendl_fd(lst->str, 1);
		lst = lst->next;
	}
	return (0);
}
