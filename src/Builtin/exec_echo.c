/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:31:23 by storck            #+#    #+#             */
/*   Updated: 2026/03/16 11:31:57 by storck           ###   ########.fr       */
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

int	check_single_dollar(char *str1, t_quote_type quote1, t_quote_type quote2)
{
	if (ft_strcmp(str1, "$"))
		return (1);
	else if (quote1 != quote2)
		return (1);
	return (0);
}

int	exec_echo(char **arg, t_quote_type *quote, t_data *data)
{
	int		i;

	i = 0;
	if (!arg || !arg[0])
		return (ft_putchar_fd('\n', STDOUT_FILENO), 0);
	while (is_option_n(arg[i]))
		i++;
	while (arg[i])
	{
		if (do_replace(arg[i], quote[i]))
			replace_var(&arg[i], data);
		if (!arg[i + 1]
			|| check_single_dollar(arg[i], quote[i], quote[i + 1]))
			ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i][0] != '\0' && arg[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (ft_strcmp(arg[0], "-n") != 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
