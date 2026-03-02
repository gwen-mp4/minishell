/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:56:12 by gwen              #+#    #+#             */
/*   Updated: 2026/03/02 15:47:18 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sigint_handler(int sig)
{
	(void) sig;
	signal(SIGINT, sigint_handler);
	g_sig = SIGINT;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_heredoc(int sig)
{
	(void) sig;
	signal(SIGINT, sigint_heredoc);
	g_sig = SIGINT;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}
void	setup_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
}

void	signal_heredoc(void)
{
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
