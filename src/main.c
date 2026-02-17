/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:54:48 by storck            #+#    #+#             */
/*   Updated: 2026/02/17 19:09:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	(void) ac;
	(void) av;
	(void) env;
	while (1)
	{
		setup_signal();
		//init_data(&data, env);
		data.line = readline("$> ");
		if (!data.line)
			break ;
		if (*data.line)
			add_history(data.line);
		data.token = lexer(data.line);
		if (!data.token)
			clean_tokens(data.token);
		check_list(data.token);
		//printf("%s\n", data.line);
		//interpret(&data);
		free(data.line);
		clean_tokens(data.token);
	}
	rl_clear_history();
	return (0);
}
