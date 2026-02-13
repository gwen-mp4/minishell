/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:54:48 by storck            #+#    #+#             */
/*   Updated: 2026/02/13 14:27:03 by gwen             ###   ########.fr       */
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

/*Function to convert type into string for lexing test*/
const char	*token_type_str(t_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == INPUT)
		return ("INPUT");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == OUTPUT)
		return ("OUTPUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == PIPE)
		return ("PIPE");
	return ("UNKNOWN");
}

//Funcion to test the token list.
void	check_list(t_token *token)
{
	while (token)
	{
		printf("%s: %s\n", token_type_str(token->type), token->value);
		token = token->next;
	}
}


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
		check_list(data.token);
		printf("%s\n", data.line);
		interpret(&data);
		free(data.line);
		error_cleanup(data.token);
	}
	rl_clear_history();
	return (0);
}
