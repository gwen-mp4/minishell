/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <storck@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:54:48 by storck            #+#    #+#             */
/*   Updated: 2026/03/04 16:38:26 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_sig;

// void	print_cmd(t_cmd *cmd, t_data *data)
// {
// 	int		i;
// 	t_cmd	*tmp;
// 	t_var	*tmp2;

// 	tmp = cmd;
// 	tmp2 = data->vars;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp->av[i])
// 		{
// 			printf("[%d] : %s\n", i, tmp->av[i]);
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	while (tmp2)
// 	{
// 		printf ("%s = %s\n", tmp2->name, tmp2->content);
// 		tmp2 = tmp2->next;
// 	}
// }

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
		data.token = lexer(data.line);
		if (!data.token)
		{
			free(data.line);
			continue;
		}
		data.cmd = parsing(data.token, &data);
		if (!data.cmd)
		{
			free(data.line);
			continue;
		}
		filter_var(data.cmd, &data);
		//print_cmd(data.cmd, &data);
		execution(data.cmd, &data);
		//interpret(&data);
		free(data.line);
		clean_tokens(data.token);
		free_cmds(data.cmd);
	}
	rl_clear_history();
	return (0);
}
