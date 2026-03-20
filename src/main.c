/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:54:48 by storck            #+#    #+#             */
/*   Updated: 2026/03/19 14:04:39 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig;

t_cmd	*lexing_and_parsing(t_data *data)
{
	t_cmd	*ret;

	data->token = lexer(data->line, data);
	if (!data->token)
		return (NULL);
	ret = parsing(data->token, data);
	if (!ret)
	{
		clean_tokens(data->token);
		data->token = NULL;
		return (NULL);
	}
	return (ret);
}

void	reset_line(t_data *data)
{
	free(data->line);
	data->line = NULL;
}

void	do_line(t_data *data)
{
	char	*tmp;

	if (!data->cmd->next && !data->cmd->redirs && !data->cmd->av[1]
		&& data->cmd->av[0][0] == '$')
	{
		filter_var(data->cmd, data);
		if (data->cmd->av[0])
		{
			tmp = ft_strdup(data->cmd->av[0]);
			clean_tokens(data->token);
			free_cmds(data->cmd);
			reset_line(data);
			data->line = tmp;
			data->cmd = lexing_and_parsing(data);
			filter_var(data->cmd, data);
		}
	}
	else
		filter_var(data->cmd, data);
	execution(data->cmd, data);
	reset_line(data);
	clean_tokens(data->token);
	data->token = NULL;
	free_cmds(data->cmd);
	data->cmd = NULL;
}

void	set_g_sig(t_data *data)
{
	data->exit_code = 130;
	g_sig = 0;
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
		if (g_sig == SIGINT)
			set_g_sig(&data);
		if (*data.line)
			add_history(data.line);
		data.cmd = lexing_and_parsing(&data);
		if (!data.cmd)
		{
			reset_line(&data);
			continue ;
		}
		do_line(&data);
	}
	rl_clear_history();
	return (ft_putstr_fd("exit\n", STDOUT_FILENO), free_data(&data), 0);
}
