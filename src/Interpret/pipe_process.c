/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:27:33 by storck            #+#    #+#             */
/*   Updated: 2026/03/09 12:02:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_fd(int old_fd, int new_fd)
{
	if (old_fd == new_fd)
		return ;
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(old_fd);
}

int	file_read_process(char *infile)
{
	int	fd_in;

	fd_in = open(infile, O_RDONLY, 0644);
	if (fd_in == -1)
	{
		ft_putstr_fd("open ", 2);
		perror(infile);
		return (-1);
	}
	return (fd_in);
}

int	file_write_process(char *outfile)
{
	int	fd_out;

	fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		ft_putstr_fd("open ", 2);
		perror(outfile);
		return (-1);
	}
	return (fd_out);
}
