/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:32:23 by storck            #+#    #+#             */
/*   Updated: 2026/03/19 10:23:49 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ato_exit_code(char *str, int *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					sign;

	i = 0;
	sign = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	j = i;
	while (str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + (str[i++] - '0');
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((sign == -1 && (ret - 1) > LONG_MAX)
			|| (sign == 1 && (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * sign) % 256));
}

void	err_exit(t_data *data, char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free_data(data);
	exit (2);
}

void	exit_ret(t_data *data, int ret)
{
	free_data(data);
	exit(ret);
}

void	exec_exit(char **args, t_data *data)
{
	int	ret;
	int	err;

	ret = 0;
	err = 0;
	if (args[1] && args[1][0] == '\0')
		err_exit(data, args[1]);
	if (args[1])
	{
		ret = ato_exit_code(args[1], &err);
		if (err)
			err_exit(data, args[1]);
	}
	if (args[1] && args[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		data->exit_code = 1;
		return ;
	}
	if (!args[1])
	{
		ret = data->exit_code;
		exit_ret(data, ret);
	}
	exit_ret(data, ret);
}
