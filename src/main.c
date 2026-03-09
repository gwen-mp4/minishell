/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:54:48 by storck            #+#    #+#             */
/*   Updated: 2026/03/09 18:51:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig;

t_cmd	*lexing_and_parsing(t_data *data)
{
	t_cmd	*ret;

	data->token = lexer(data->line);
	if (!data->token)
	{
		free(data->line);
		return (NULL);
	}
	ret = parsing(data->token, data);
	if (!ret)
	{
		free(data->line);
		return (NULL);
	}
	return (ret);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1 || !init_data(&data, ac, av, env))
		return (1);
	while (1)
	{
		setup_signal();
		g_sig = 0;
		data.line = readline("$> ");
		if (!data.line)
			break ;
		if (*data.line)
			add_history(data.line);
		data.cmd = lexing_and_parsing(&data);
		if (!data.cmd)
			continue ;
		filter_var(data.cmd, &data);
		execution(data.cmd, &data);
		free(data.line);
		clean_tokens(data.token);
		free_cmds(data.cmd);
	}
	rl_clear_history();
	return (0);
}
