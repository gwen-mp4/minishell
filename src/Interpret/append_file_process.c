/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_file_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:01:44 by storck            #+#    #+#             */
/*   Updated: 2026/03/18 16:05:04 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_append_process(char *outfile)
{
	int	fd_out;

	if (opendir(outfile) == NULL)
		return (error_is_a_directory(outfile), -1);
	fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd_out == -1)
	{
		ft_putstr_fd("open ", 2);
		perror(outfile);
		return (-1);
	}
	return (fd_out);
}
