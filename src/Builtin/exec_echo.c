/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:31:23 by storck            #+#    #+#             */
/*   Updated: 2026/03/13 15:01:29 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_option_n(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (ft_strncmp(str, "-n", 2))
		return (0);
	i = 2;
	while (str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	exec_echo(char **arg, t_quote_type *quote, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!arg || !arg[0])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	while (is_option_n(arg[i]))
		i++;
	while (arg[i])
	{
		tmp = ft_strchr(arg[i], '$');
		if (quote[i] != SINGLE && tmp && tmp[1] != '\0')
			replace_var(&arg[i], data);
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (ft_strcmp(arg[0], "-n") != 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
