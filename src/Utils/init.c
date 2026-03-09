/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:12:18 by storck            #+#    #+#             */
/*   Updated: 2026/03/09 19:06:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_data(t_data *data, int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	data->exit_code = 0;
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDIN_FILENO;
	data->infile = NULL;
	data->outfile = NULL;
	data->env = env;
	data->envlst = NULL;
	init_envlst(data, env);
	data->pipe_count = 0;
	data->vars = NULL;
	return (1);
}
