/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: storck <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:12:18 by storck            #+#    #+#             */
/*   Updated: 2026/02/13 13:12:21 by storck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_data(t_data *data, char **env)
{
    data->exit_code = 0;
    data->fd_in = STDIN_FILENO;
    data->fd_out = STDIN_FILENO;
	data->infile = NULL;
	data->outfile = NULL;
    data->env = env;
    data->pipe_count = 0;
	return (1);
}
