/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:29:29 by storck            #+#    #+#             */
/*   Updated: 2026/03/10 11:10:31 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_env(t_list	*env)
{
	t_list	*lst;

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
