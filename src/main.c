/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:54:48 by storck            #+#    #+#             */
/*   Updated: 2026/02/11 14:09:31 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	main(int ac, char **av, char **env)
// {
// 	char	*rl;

// 	(void)ac;
// 	(void)av;
// 	(void)env;
// 	rl = readline("Minishell > ");
// 	rl = parsing(rl);
// 	printf("%s\n", rl);
// 	free (rl);
// 	return (0);
// }

int	main(void)
{
	t_data	data;

	while (1)
	{
		//setup_signal();
		data.line = readline("$> ");
		if (!data.line)
			break ;
		if (*data.line)
			add_history(data.line);
		lexer(data.line);
		printf("%s\n", data.line);
		free(data.line);
	}
	rl_clear_history();
	return (0);
}
