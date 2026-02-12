/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:56:12 by gwen              #+#    #+#             */
/*   Updated: 2026/02/12 12:16:01 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(void)
{
	char				*rd;

	while (1)
	{
		setup_signal();
		rd = readline("$> ");
		if (!rd)
		{
			printf("Exiting minishell\n");
			free(rd);
			break ;
		}
		if (*rd)
			add_history(rd);
		printf("%s\n", rd);
		free(rd);
	}
	rl_clear_history();
	return (0);
}
