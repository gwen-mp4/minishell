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

//Funcion to test the token list.
/*
void	check_list(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		printf("%d : ", tmp->type);
		if (tmp->value)
			printf("%s", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}
*/

int	main(int ac, char **av, char **env)
{
	t_data	data;

	while (1)
	{
		//setup_signal();
		init_data(&data, env);
		data.line = readline("$> ");
		if (!data.line)
			break ;
		if (*data.line)
			add_history(data.line);
		data.token = lexer(data.line);
		//check_list(data.token);
		printf("%s\n", data.line);
		interpret(&data);
		free(data.line);
		//error_cleanup(&data.token);
	}
	rl_clear_history();
	return (0);
}
