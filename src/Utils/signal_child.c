/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:14:05 by gwen              #+#    #+#             */
/*   Updated: 2026/03/04 15:18:37 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sigint_handler(int sig)
{
	(void) sig;
	g_sig = SIGINT;
	write(2, "\n", 1);
	rl_done = 1;
}

static int	sig_hook(void)
{
	return (EXIT_SUCCESS);
}

void	signal_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	rl_event_hook = sig_hook;
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}
