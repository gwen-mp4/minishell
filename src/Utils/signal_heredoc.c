/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:13:56 by gwen              #+#    #+#             */
/*   Updated: 2026/03/06 13:12:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sigint_heredoc(int sig)
{
	(void) sig;
	g_sig = SIGINT;
	rl_done = 1;
}

static int	sig_hook(void)
{
	return (EXIT_SUCCESS);
}

void	signal_heredoc(void)
{
	struct sigaction	sa;

	rl_done = 0;
	rl_event_hook = sig_hook;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_heredoc;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
