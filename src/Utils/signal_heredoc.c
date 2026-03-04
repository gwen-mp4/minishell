/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:13:56 by gwen              #+#    #+#             */
/*   Updated: 2026/03/04 15:18:08 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sigint_heredoc(int sig)
{
	(void) sig;
	g_sig = SIGINT;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
}

static int	sig_hook(void)
{
	return (EXIT_SUCCESS);
}

void	signal_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	rl_event_hook = sig_hook;
	sa.sa_flags = 0;
	sa.sa_handler = sigint_heredoc;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
